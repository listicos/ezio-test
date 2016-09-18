/* -----------------------------------------------------------------------------
 *
 *     Copyright (c) 2015  GEMALTO DEVELOPPEMENT - R&D
 *
 * ------------------------------------------------------------------------------
 * GEMALTO MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. GEMALTO SHALL NOT BE
 * LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 *
 * THIS SOFTWARE IS NOT DESIGNED OR INTENDED FOR USE OR RESALE AS ON-LINE
 * CONTROL EQUIPMENT IN HAZARDOUS ENVIRONMENTS REQUIRING FAIL-SAFE
 * PERFORMANCE, SUCH AS IN THE OPERATION OF NUCLEAR FACILITIES, AIRCRAFT
 * NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL, DIRECT LIFE
 * SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH THE FAILURE OF THE
 * SOFTWARE COULD LEAD DIRECTLY TO DEATH, PERSONAL INJURY, OR SEVERE
 * PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH RISK ACTIVITIES"). GEMALTO
 * SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR
 * HIGH RISK ACTIVITIES.
 *
 * ------------------------------------------------------------------------------
 */

#import "ViewController.h"
#import "FakeAppData.h"
#import "QuartzCore/QuartzCore.h"
#import "AppDelegate.h"

@interface ViewController ()

@property (nonatomic, weak) IBOutlet UITextView *scrollText;
@property (nonatomic, weak) IBOutlet UITableView *tableView;
@property NSString *domain;
@property NSString *applicationId;
@property NSString *providerId;
@property NSURL *oobClientUrl;
@property NSData *rsaModulus;
@property NSData *rsaExponent;
@property NSDictionary *meta;

@end

@implementation ViewController

AppDelegate *appDelegate;
UIActivityIndicatorView *mSpinner;
UIAlertView *message;
UIView *loadingView;

NSString* resultMessage;
NSMutableArray *messageQueue;

EMCore *context;
id<EMPasswordManager> passwordManager;
id<EMOobFetchMessageResponse> popMessage;
id<EMOobIncomingMessage> oobIncomingMessage;
NSString *clientCode;
id<EMOobManager> oobManager;
EMOobModule *oobModule;



#pragma mark - Initialization
// The entry point for Ezio Mobile SDK.
// SDK create databases and files on behalf of the application.
- (void)internalInit
{
    if (self)
    {
        [self loadSpinnerWithMessage:@"Initializing.."];
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
            [self loginEzio];
            dispatch_async(dispatch_get_main_queue(), ^{
                self.scrollText.text = [@"\n\nEzio Initialized!" stringByAppendingString:self.scrollText.text];
                [self hideSpinner];
            });
        });

    }
    _meta = FakeAppData.meta;
}


// Initalize OobFactory with configurations
- (void) initializeOob{
    EMOobConfiguration *oobConfiguration;
    
    oobConfiguration = [EMOobConfiguration configurationWithOptionalParameters:
                        ^(EMOobConfigurationBuilder *configurationBuilder) {
                            
                            configurationBuilder.deviceFingerprintSource = [[EMDeviceFingerprintSource alloc] initWithDeviceFingerprintType:[NSSet setWithObject:@(EMDeviceFingerprintTypeSoft)]];
                            
#ifdef DEBUG
                            configurationBuilder.tlsConfiguration = [[EMTlsConfiguration alloc] initWithInsecureConnectionAllowed:NO
                                                                                                            selfSignedCertAllowed:NO
                                                                                                          hostnameMismatchAllowed:NO
                                                                                                                          timeout:30];
                            
                            configurationBuilder.jailbreakPolicy = EMOobJailbreakPolicyIgnore;
#else
                            configurationBuilder.tlsConfiguration = [[EMTlsConfiguration alloc] init];
                            configurationBuilder.jailbreakPolicy = EMOobJailbreakPolicyFail;
#endif
                        }];
    
    context = [EMCore configureWithActivationCode:FakeAppData.activationCode configurations:[NSSet setWithObjects:oobConfiguration,
                                                                                             nil]];
}

//login SDK
- (void)loginEzio{
    /* Configuration */
    _domain = FakeAppData.domain;
    _applicationId = FakeAppData.applicationId;
    _providerId = FakeAppData.providerId;
    _oobClientUrl= FakeAppData.oobClientUrl;
    _rsaExponent = FakeAppData.rsaExponent;
    _rsaModulus = FakeAppData.rsaModulus;
    
    // Login to all domains, may need to prompt for password from the user
    [self initializeOob];
    passwordManager = [context passwordManager];
    NSError *error;
    [passwordManager login:&error];
    if (error!=nil){
        self.scrollText.text = [[error localizedDescription] stringByAppendingString:self.scrollText.text];
        return;
    }
    
}



#pragma mark - OOB
/**
 * register the client
 * userId userId during enrolment
 * userAlias userAlias
 * registrationCode registrationCode obtained from the provider
 */
- (void) registerEzio:(NSString *)userId userAlias:(NSString *)userAlias regCode:(NSString *)regCode{
    NSError *error;
    
    [self loadSpinnerWithMessage:@"Registering.."];
    
    //get registrationcode as secureString
    id<EMSecureString> registrationCode = [[context secureContainerFactory] secureStringFromString:regCode];
    
    // create OobRegistrationManager object
    
    oobModule = [EMOobModule oobModule];
    
    oobManager = [oobModule createOobManagerWithURL:_oobClientUrl
                                             domain:_domain
                                      applicationId:_applicationId
                                        rsaExponent:_rsaExponent
                                         rsaModulus:_rsaModulus
                                              error:nil];
    id<EMOobRegistrationManager> oobRegistrationManager = [oobManager oobRegistrationManager];
    // create OobRegistrationRequest object
    EMOobRegistrationRequest *oobRegistrationRequest =
    [[EMOobRegistrationRequest alloc] initWithUserId:userId
                                  userAliasForClient:userAlias
                                  registrationMethod:EMOobRegistrationMethodRegistrationCode
                               registrationParameter:registrationCode
                                               error:&error];
    
    if(error!=nil){
        self.scrollText.text = [[error localizedDescription] stringByAppendingString:self.scrollText.text];
        return;
        
    }
    
    [oobRegistrationManager registerWithRequest:oobRegistrationRequest
                              completionHandler:^(id<EMOobRegistrationResponse> aResponse,NSError *error) {
                                  
                                  [self hideSpinner];
                                  resultMessage = [aResponse clientId];
                                  
                                  if ([aResponse resultCode] == EMOobResultCodeSuccess)
                                  {
                                      self.scrollText.text = [[@"\n\nClient Registered!. ClientId: " stringByAppendingString:resultMessage] stringByAppendingString:self.scrollText.text];
                                      
                                      // persistent storage to manager clientId
                                      // developer can choose sqlite database
                                      NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
                                      [defaults setObject:resultMessage forKey:@"clientId"];
                                      [defaults synchronize];
                                      
                                      //set Notification PRofile
                                      [self setNotificationProfile];
                                      
                                  } else
                                  {
                                      self.scrollText.text = [[@"\n\nSomer Error Occured! ClientId: " stringByAppendingFormat:@"%@",error]stringByAppendingString:self.scrollText.text];
                                      [self hideSpinner];
                                  } }];
}


- (NSString *) clientCode{
    // Retrieve the corresponding clientId
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSString *clientCode = [defaults objectForKey:@"clientId"];
    return clientCode;
}


/**
 * Fetch message
 * messageId
 */
- (void) fetchMessage{
    if (clientCode==nil) {
        self.scrollText.text = [@"\n\nCanNot Fetch, Clientcode is nil. Please Register!" stringByAppendingString:self.scrollText.text];
        return;
    }else{
        if(!mSpinner){
            [self loadSpinnerWithMessage:@"Fetching Messages.."];
            
        }else{
            [self hideSpinner];
            [self loadSpinnerWithMessage:@"Fetching Messages.."];
        }
    }
    
    // create OobMessageManager object
    id<EMOobMessageManager> oobMessageManager = [oobManager oobMessageManagerWithClientId:clientCode providerId:_providerId];
    [oobMessageManager fetchWithTimeout:30000 completionHandler: // you can fetch with timeout value or fetch with messageId(ie. obtained from APNS)
     ^(id<EMOobFetchMessageResponse> aResponse, NSError *error) {
         
         [self hideSpinner];
         if ([aResponse resultCode] == EMOobResultCodeSuccess)
         {
             if ([aResponse oobIncomingMessage]) {
                 [messageQueue addObject:aResponse];
                 messageQueue = [[[messageQueue reverseObjectEnumerator] allObjects] mutableCopy];
                 [self.tableView reloadData];
             }else{
                 self.scrollText.text = [@"\n\nNo Incoming Message!" stringByAppendingString:self.scrollText.text];
             }
             
             
         } else {
             [self hideSpinner];
             // handle the error
             self.scrollText.text = [[@"\n\nSomer Error Occured while Fetching Messages! " stringByAppendingFormat:@"%@",error] stringByAppendingString:self.scrollText.text];
         } }];
}


- (void) fetchMessageWithId:(NSString *)messageId{
    if (clientCode==nil) {
        self.scrollText.text = [@"\n\nCanNot Fetch, Clientcode is nil. Please Register!" stringByAppendingString:self.scrollText.text];
        return;
    }else{
        if(!mSpinner){
            [self loadSpinnerWithMessage:@"Fetching Messages.."];
            
        }else{
            [self hideSpinner];
            [self loadSpinnerWithMessage:@"Fetching Messages.."];
        }
    }
    // create OobMessageManager object
    id<EMOobMessageManager> oobMessageManager = [oobManager oobMessageManagerWithClientId:clientCode providerId:_providerId];
    
    [oobMessageManager fetchWithMessageId:messageId completionHandler: // you can fetch with timeout value or fetch with messageId(ie. obtained from APNS)
     ^(id<EMOobFetchMessageResponse> aResponse, NSError *error) {
         
         [self hideSpinner];
         
         if ([aResponse resultCode] == EMOobResultCodeSuccess)
         {
             if ([aResponse oobIncomingMessage]) {
                 [messageQueue addObject:aResponse];
                 messageQueue = [[[messageQueue reverseObjectEnumerator] allObjects] mutableCopy];
                 [self.tableView reloadData];
             }else{
                 self.scrollText.text = [@"\n\nNo Incoming Message!" stringByAppendingString:self.scrollText.text];
             }
             
         } else {
             [self hideSpinner];
             
             // handle the error
             self.scrollText.text = [[@"\n\nSomer Error Occured while Fetching Messages! " stringByAppendingFormat:@"%@",error] stringByAppendingString:self.scrollText.text];
         } }];
}


/**
 * Handle the message fetched from server
 * @param message
 */
- (void) handleIncomingMessage:(id<EMOobIncomingMessage>)message{
    // get messageType
    NSString *messageType = [message messageType];
    
    // check messageType, cast to specific type and handle it
    if ([messageType isEqual:EMOobIncomingMessageTypeGeneric]){
        id<EMOobGenericIncomingMessage> genericMsg = (id<EMOobGenericIncomingMessage>)message;
        
        // Actions:
        // 1. check if acknowledgement required
        if([genericMsg isAcknowledgmentRequested]){
            // acknowledge message
            [self acknowledgeMessage:genericMsg];
        }
        // 2. send error if the content is corrupted or ...
        [self createErrorResponse:genericMsg];
        
    }else if ([messageType isEqual:EMOobIncomingMessageTypeUserMessage]){
        id<EMOobProviderToUserMessage> userMsg = (id<EMOobProviderToUserMessage>)message;
        // Actions:
        // 1. check if acknowledgement required
        if([userMsg isAcknowledgmentRequested]){
            // acknowledge message
            [self acknowledgeMessage:userMsg];
        }
        
        // 2. send error if the content is corrupted or ...
        [self createErrorResponse:userMsg];
        // 3. Send message to provider
        [self replyUserMessage:userMsg];
        
    }else if ([messageType isEqual:EMOobIncomingMessageTypeTransactionVerify]){
        
        id<EMOobTransactionVerifyRequest> txtMsg = (id<EMOobTransactionVerifyRequest>)message;
        // Actions:
        // 1. check if acknowledgement required
        if([txtMsg isAcknowledgmentRequested]){
            // acknowledge message
            [self acknowledgeMessage:txtMsg];
        }
        // 2. send error if the content is corrupted or ...
        [self createErrorResponse:txtMsg];
        // 3. accept/reject transaction verification request
        [self handleTransactionVerification:txtMsg response:EMOobTransactionVerifyResponseValueAccepted];
    }
    
}


/**
 * explicitly create error response
 * @param message
 */
- (void) createErrorResponse:(id<EMOobIncomingMessage>)message{
    // create OobMessageManager object
    id<EMOobMessageManager> oobMessageManager = [oobManager oobMessageManagerWithClientId:clientCode providerId:_providerId];
    [self loadSpinnerWithMessage:@"Sending Error Report.."];
    
    // Create error from incoming message
    // Or create it from messageManager
    id<EMOobErrorMessage> oobErr = [message createOobError:EMOobErrorMessageCodeCustomBase
                                          errorDescription:@"description" errorStackTrace:@"stackTrace" externalRef:nil meta:_meta];
    
    [oobMessageManager sendWithMessage:oobErr completionHandler:^(id<EMOobMessageResponse> aResponse, NSError *anError) {
        if ([aResponse resultCode]==EMOobResultCodeSuccess) {
            //update ui , error report sent
            self.scrollText.text = [@"\n\nError Message Sent!" stringByAppendingString:self.scrollText.text];
            
        }else{
            // handle error response
            [self handleErrorResponse:aResponse];
            
        }
        
    }];
    
}


/**
 * handle transaction verification request
 * @param response
 * @param value Accept or Deny
 */
- (void) handleTransactionVerification:(id<EMOobTransactionVerifyRequest>)message response:(EMOobTransactionVerifyResponseValue)value{
    // create OobMessageManager object
    id<EMOobMessageManager> oobMessageManager = [oobManager oobMessageManagerWithClientId:clientCode providerId:_providerId];
    
    // Create the response from incoming request object
    // Or create it from messageManager
    id<EMOobTransactionVerifyResponse> oobTransactionVerifyResponse = [message createWithResponse:value meta:_meta];
    
    NSString *action = @"Accepting Transaction";
    if(value==EMOobTransactionVerifyResponseValueRejected){
        action = @"Rejecting Transaction..";
        
    }
    
    if(!mSpinner){
        [self loadSpinnerWithMessage:action];
    }else{
        [self hideSpinner];
        [self loadSpinnerWithMessage:action];
    }
    
    //send reply message
    [oobMessageManager sendWithMessage:(id<EMOobOutgoingMessage>)oobTransactionVerifyResponse completionHandler:^(id<EMOobMessageResponse> aResponse, NSError *anError) {
        [self hideSpinner];
        
        if ([aResponse resultCode]==EMOobResultCodeSuccess) {
            [self removeMessage:popMessage displayText:@"\n\nTransaction Response Sent!"];
        }else{
            // handle error response
            [self handleErrorResponse:aResponse];
        }
    }];
}


/**
 * Reply to provider to user message or send user to provider message
 * @param message
 */
- (void) replyUserMessage:(id<EMOobProviderToUserMessage>)message{
    // create OobMessageManager object
    id<EMOobMessageManager> oobMessageManager = [oobManager oobMessageManagerWithClientId:clientCode providerId:_providerId];
    
    if(!mSpinner){
        [self loadSpinnerWithMessage:@"Sending Reply.."];
    }else{
        [self hideSpinner];
        [self loadSpinnerWithMessage:@"Sending Reply.."];
    }
    
    // Create outgoing message from incoming message
    // Or create it from messageManager
    id<EMOobUserToProviderMessage> outMsg = [message createResponseWithLocale:@"SG" createTime:NSTimeIntervalSince1970 subject:[[context secureContainerFactory] secureStringFromString:@"Subject"] from:@"From" contentType:@"text/plain" content: [[context secureContainerFactory] secureStringFromString:@"Content"] attachments:nil meta:_meta];
    
    [oobMessageManager sendWithMessage:outMsg completionHandler:^(id<EMOobMessageResponse> aResponse, NSError *anError) {
        [self hideSpinner];
        
        if ([aResponse resultCode]==EMOobResultCodeSuccess) {
            [self removeMessage:popMessage displayText:@"\n\nUser Message Sent!."];
            
        }else{
            // handle error response
            [self handleErrorResponse:aResponse];
        }
        
    }];
}


/**
 * Acknowledge a message when needed
 * @param message
 */
- (void) acknowledgeMessage:(id<EMOobIncomingMessage>)message {
    // create OobMessageManager object
    id<EMOobMessageManager> oobMessageManager = [oobManager oobMessageManagerWithClientId:clientCode providerId:_providerId];
    
    
    if(!mSpinner){
        [self loadSpinnerWithMessage:@"Sending Acknowledge.."];
    }else{
        [self hideSpinner];
        [self loadSpinnerWithMessage:@"Sending Acknowledge.."];
    }
    [oobMessageManager acknowledgeWithMessage:message completionHandler:^(id<EMOobResponse> aResponse, NSError *anError) {
        [self hideSpinner];
        
        if ([aResponse resultCode]==EMOobResultCodeSuccess) {
            [self removeMessage:popMessage displayText:@"\n\nMessage Acknowledged!"];
            
        }else{
            // handle error response
            [self handleErrorResponse:aResponse];
        }
    }];
}


//create message out of an incoming message
- (NSString *) descriptionWithIncomingMessage:(id<EMOobIncomingMessage>) anOobIncomingMessage{
    NSString *messageDetailsWithExp;
    NSString *messageDetails;
    NSString *messageContent;
    NSString *messageSubject;
    NSString *messageFrom;
    NSString *messageTo;
    NSString *messageReplyto;
    
    if(anOobIncomingMessage){
        
        if ([[anOobIncomingMessage messageType] isEqual:EMOobIncomingMessageTypeGeneric]) {
            messageContent = [[(id<EMOobGenericIncomingMessage>)anOobIncomingMessage contentString] stringValue];
            messageDetails = [NSString stringWithFormat:@"Generic Message Details:\n %@", messageContent];
            
        }else if ([[anOobIncomingMessage messageType] isEqual:EMOobIncomingMessageTypeUserMessage]){
            messageContent = [[(id<EMOobProviderToUserMessage>)anOobIncomingMessage contentString] stringValue];
            messageSubject = [[(id<EMOobProviderToUserMessage>)anOobIncomingMessage subject] stringValue];
            messageFrom = [(id<EMOobProviderToUserMessage>)anOobIncomingMessage from] ;
            messageTo = [(id<EMOobProviderToUserMessage>)anOobIncomingMessage to] ;
            messageReplyto = [(id<EMOobProviderToUserMessage>)anOobIncomingMessage replyTo] ;
            messageDetails = [NSString stringWithFormat:@"User Message Details:\n %@ Subject: %@ From: %@ To: %@ ReplyTo: %@", messageContent, messageSubject,messageFrom, messageTo, messageReplyto];
            
        }else if ([[anOobIncomingMessage messageType] isEqual:EMOobIncomingMessageTypeTransactionVerify]){
            messageContent = [[(id<EMOobTransactionVerifyRequest>)anOobIncomingMessage contentString] stringValue];
            messageSubject = [[(id<EMOobTransactionVerifyRequest>)anOobIncomingMessage subject] stringValue];
            messageDetails = [NSString stringWithFormat:@"Transaction Verify Message Details:\n %@ ", messageContent];
        }
        
        NSTimeInterval lastUpdate = [anOobIncomingMessage expirationDate];
        NSDate *_expDate = [[NSDate alloc] initWithTimeIntervalSince1970:lastUpdate];
        
        NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
        [dateFormatter setDateStyle:NSDateFormatterMediumStyle];
        [dateFormatter setTimeStyle:NSDateFormatterMediumStyle];
        
        
        NSString *displayDate = [NSString stringWithFormat:@" Expiration Date: %@",[dateFormatter stringFromDate:_expDate]];
        messageDetailsWithExp = [[messageDetails stringByAppendingString:displayDate] stringByAppendingString:[anOobIncomingMessage messageId] ];
        return messageDetailsWithExp;
        
    }else{
        //update on UI no msg found
        self.scrollText.text = [@"\n\nNo Message Available!" stringByAppendingString:self.scrollText.text];
        return 0;
    }
}


- (void) didUnRegister{
    // unregistration from OOB asynchronously
    id<EMOobUnregistrationManager> oobUnregistrationManager = [oobManager
                                                               oobUnregistrationManagerWithClientId:clientCode];
    [oobUnregistrationManager unregisterWithCompletionHandler:^(id<EMOobResponse>
                                                                aResponse, NSError *error) {
        
        if ([aResponse resultCode] == EMOobResultCodeSuccess)
        {
            // Retrieve the corresponding clientId and remove it
            NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
            [defaults removeObjectForKey:@"clientId"];
            [defaults synchronize];
            
            self.scrollText.text = [@"\n\nClient Unregistered!" stringByAppendingString:self.scrollText.text];
            [self removeAllMessages];
            [self hideSpinner];
            
        } else {
            self.scrollText.text = [[@"\n\nSomer Error Occured while Unregistration!" stringByAppendingFormat:@"%@",error] stringByAppendingString:self.scrollText.text];
            [self hideSpinner];
            
        } }];
}


/**
 * Extract error message from response object
 * @param response
 */
- (void) handleErrorResponse:(id<EMOobResponse>)response {
    // Get Information from the response and display it
    self.scrollText.text = [[@"\n\nSome Error Occured in response from Server!\nResultCode: " stringByAppendingFormat:@"%lu",(unsigned long)[response resultCode]] stringByAppendingString:self.scrollText.text];
    [self hideSpinner];
}


#pragma mark - UI
//a spinner animation for processing wait
- (void) loadSpinnerWithMessage:(NSString *)loadMessage{
    UILabel *_loadingLabel;
    
    loadingView = [[UIView alloc] initWithFrame:CGRectMake(self.view.center.x,self.view.center.y, self.view.frame.size.width/2, self.view.frame.size.height/4)];
    loadingView.center = self.view.center;
    
    loadingView.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0.5];
    loadingView.clipsToBounds = YES;
    loadingView.layer.cornerRadius = 10.0;
    
    mSpinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    mSpinner.frame = CGRectMake((loadingView.frame.size.width - mSpinner.bounds.size.width) / 2, ((loadingView.frame.size.height - mSpinner.bounds.size.height) / 2) - 45.0f, mSpinner.bounds.size.width, mSpinner.bounds.size.height);

    [loadingView addSubview:mSpinner];
    
    _loadingLabel = [[UILabel alloc] initWithFrame:CGRectMake(20.0f, mSpinner.frame.origin.y + mSpinner.frame.size.height + 20, loadingView.frame.size.width - 40.0f, 25.0f)];
    _loadingLabel.backgroundColor = [UIColor clearColor];
    _loadingLabel.textColor = [UIColor whiteColor];
    _loadingLabel.adjustsFontSizeToFitWidth = YES;
    _loadingLabel.textAlignment = NSTextAlignmentCenter;
    _loadingLabel.text = loadMessage;
    [loadingView addSubview:_loadingLabel];
    
    [self.view addSubview:loadingView];
    [mSpinner startAnimating];
}


- (void) hideSpinner{
    [mSpinner stopAnimating];
    [loadingView removeFromSuperview];
}


//popup actions
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSString *title = [alertView buttonTitleAtIndex:buttonIndex];
    
    if([title isEqualToString:@"Yes"])
    {   //unregister and clear notification profile
        [self clearNotifiactionProfile];
        
    }
    else if([title isEqualToString:@"OK"])
    {
        [self registerEzio:FakeAppData.userId userAlias:FakeAppData.userAlias regCode:[message textFieldAtIndex: 0].text];
        
    }
    else if([title isEqualToString:@"Cancel"])
    {
        self.scrollText.text = [@"\n\nOpCanceled!" stringByAppendingString:self.scrollText.text];
    }
    else if([title isEqualToString:@"Accept"])
    {
        [self handleTransactionVerification:(id<EMOobTransactionVerifyRequest>)oobIncomingMessage response:EMOobTransactionVerifyResponseValueAccepted];
        self.scrollText.text = [@"\nMessage Accepted!." stringByAppendingString:self.scrollText.text];
    }
    else if([title isEqualToString:@"Reject"])
    {
        [self handleTransactionVerification:(id<EMOobTransactionVerifyRequest>)oobIncomingMessage response:EMOobTransactionVerifyResponseValueRejected];
        self.scrollText.text = [@"\nMessage Rejected!" stringByAppendingString:self.scrollText.text];
        
    }else if([title isEqualToString:@"Acknowledge"])
    {
        [self acknowledgeMessage:oobIncomingMessage];
        
    }else if([title isEqualToString:@"Ignore"])
    {
        [self removeMessage:popMessage displayText:@"\n\nMessage Ignored!"];
        [self hideSpinner];
        
    }else if([title isEqualToString:@"Reply"])
    {
        [self replyUserMessage:(id<EMOobProviderToUserMessage>)oobIncomingMessage];
    }
    
}

//remove selected cell message
- (void) removeMessage:(id<EMOobFetchMessageResponse>) cellMessage displayText:(NSString *) dispText{
    
    if([messageQueue containsObject:cellMessage]){
        [messageQueue removeObjectAtIndex:[messageQueue indexOfObject:cellMessage]];
        [self.tableView reloadData];
        self.scrollText.text = [dispText stringByAppendingString:self.scrollText.text];
    }else{
        self.scrollText.text = [@"\n\nAction Aleady Taken!. Please Wait..." stringByAppendingString:self.scrollText.text];
    }
    
}

//remove All cell message
- (void) removeAllMessages{
    [messageQueue removeAllObjects];
    [self.tableView reloadData];
    self.scrollText.text = [@"\n\nCleared All Messages Locally!" stringByAppendingString:self.scrollText.text];
    return;
}


//popup message details
- (void) showUserActionsForOOBMessage:(id<EMOobIncomingMessage>)messageType withText:(NSString *)descText{
    
    if ([[oobIncomingMessage messageType] isEqual:EMOobIncomingMessageTypeGeneric]) {
        message = [[UIAlertView alloc] initWithTitle:@"Generic Message!"
                                             message:descText
                                            delegate:self
                                   cancelButtonTitle:@"Acknowledge"
                                   otherButtonTitles: nil];
        
    }else if ([[oobIncomingMessage messageType] isEqual:EMOobIncomingMessageTypeUserMessage]){
        message = [[UIAlertView alloc] initWithTitle:@"User Message!"
                                             message:descText
                                            delegate:self
                                   cancelButtonTitle:@"Cancel"
                                   otherButtonTitles:@"Reply", @"Ignore",  nil];
        
    }else if ([[oobIncomingMessage messageType] isEqual:EMOobIncomingMessageTypeTransactionVerify]){
        message = [[UIAlertView alloc] initWithTitle:@"Transaction Verify!"
                                             message:descText
                                            delegate:self
                                   cancelButtonTitle:@"Cancel"
                                   otherButtonTitles:@"Accept", @"Reject",  nil];
    }
    
    [message show];
}


//fetch message request
- (IBAction)getMessage:(id)sender {
    [self fetchMessage];
}


//Unregister
- (IBAction)unRegister:(id)sender {
    if(clientCode ==nil){
        self.scrollText.text = [@"\n\nCanNot Unregister. Client Code is nil, Register First!" stringByAppendingString:self.scrollText.text];
        return;
    }
    
    message = [[UIAlertView alloc] initWithTitle:@"UnRegister"
                                         message:@"Are you Sure?"
                                        delegate:self
                               cancelButtonTitle:@"Yes"
                               otherButtonTitles:@"Cancel", nil];
    message.alertViewStyle = UIAlertViewStyleDefault;
    
    [message show];
}


//register popup
- (IBAction)showRegister:(id)sender {
    message = [[UIAlertView alloc] initWithTitle:@"Register"
                                         message:@"Enter Registration Code!"
                                        delegate:self
                               cancelButtonTitle:@"OK"
                               otherButtonTitles:@"Cancel", nil];
    message.alertViewStyle = UIAlertViewStylePlainTextInput;
    
    [message show];
}

#pragma mark - Tableview delegate
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [messageQueue count];
}


//inserts messages in uitableview
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *simpleTableIdentifier = @"SimpleTableCell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:simpleTableIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:simpleTableIdentifier];
    }
    
    NSString *cellContent = [self descriptionWithIncomingMessage:[[messageQueue objectAtIndex:indexPath.row] oobIncomingMessage]];
    cell.textLabel.text = cellContent;
    return cell;
}


//show message details of selected cell
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    id<EMOobFetchMessageResponse> response = messageQueue[indexPath.row];
    oobIncomingMessage = [response oobIncomingMessage];
    [self showUserActionsForOOBMessage:oobIncomingMessage withText:[self descriptionWithIncomingMessage:oobIncomingMessage]];
    popMessage = response;
}


//some table cell decoration
- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    cell.backgroundColor = [UIColor lightGrayColor];
    [cell.layer setCornerRadius:7.0f];
    [cell.layer setMasksToBounds:YES];
    [cell.layer setBorderWidth:2.0f];
}

#pragma mark - Life Cycle and Notification

- (void)viewDidLoad {
    
    [super viewDidLoad];
    appDelegate = [[UIApplication sharedApplication] delegate];
    
    // Do any additional setup after loading the view, typically from a nib.
    messageQueue = [[NSMutableArray alloc] init];
    self.tableView.separatorColor = [UIColor clearColor];
    
    //remove table view background
    self.tableView.opaque = NO;
    self.tableView.backgroundColor = [UIColor clearColor];
    self.tableView.backgroundView  = nil;
    
    //start here initialization
    [self internalInit];
    
    NSString *notification = @"PushDelivered";
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveNotification:) name:notification object:nil];
}


- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    // Security Guideline: AND01. Sensitive data leaks
    self.scrollText.text = @"\nCleared for Security Reasons!\n";
    
    // Logout the password manager at the end
    // Developer may choose to logout wherever appropriate for your application flow
    [passwordManager logout:NULL];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)didReceiveNotification:(id) sender
{
    if (appDelegate.messageId) {
        [self fetchMessageWithId:appDelegate.messageId];
        [[UIApplication sharedApplication] setApplicationIconBadgeNumber: 1];
        [[UIApplication sharedApplication] setApplicationIconBadgeNumber: 0];
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
    }else{
        self.scrollText.text = [@"\n\nNo Push Notification available!" stringByAppendingString:self.scrollText.text];
    }
}


-(void) setNotificationProfile{
    clientCode = [self clientCode];
    if (clientCode==nil) {
        self.scrollText.text = [@"\n\nCanNot set Notification Profile, Clientcode is nil. Please Register!" stringByAppendingString:self.scrollText.text];
        return;
    }else{
        
        // get the OOB notification manager
        id<EMOobNotificationManager> oobNotificationManager = [oobManager oobNotificationManagerWithClientId:clientCode];
        
        if (appDelegate.deviceCode) {
            self.scrollText.text = [[@"\n\nDid Register for Remote Notifications with Device Token: " stringByAppendingString:appDelegate.deviceCode] stringByAppendingString:self.scrollText.text];
            
            EMOobNotificationProfile *oobNotificationProfileItem2 = [[EMOobNotificationProfile
                                                                      alloc] initWithChannel:@"APN" endPoint:appDelegate.deviceCode];
            NSArray *notificationItems = @[oobNotificationProfileItem2];
            [oobNotificationManager setNotificationProfiles:notificationItems completionHandler:^(id<EMOobResponse> aResponse, NSError *error) {
                
                if ([aResponse resultCode] == EMOobResultCodeSuccess)
                {
                    self.scrollText.text = [@"\n\nNotification Profile Set!" stringByAppendingString:self.scrollText.text];
                    
                } else {
                    // handle the error
                    
                    self.scrollText.text = [[@"\n\nError: Notification Profile Not Set!" stringByAppendingFormat:@"%@",error] stringByAppendingString:self.scrollText.text];
                    
                    [self handleErrorResponse:aResponse];
                } }];
        }else{
            self.scrollText.text = [[@"\n\nError: Notification Profile Not Set! Device Code: " stringByAppendingFormat:@"%@",appDelegate.deviceCode] stringByAppendingString:self.scrollText.text];
        }
        [self hideSpinner];
    }
}


//clear Notification Profile
- (void) clearNotifiactionProfile{
    if(!mSpinner){
        [self loadSpinnerWithMessage:@"Unregistering.."];
    }else{
        [self hideSpinner];
        [self loadSpinnerWithMessage:@"Unregistering.."];
    }
    
    // get the OOB notification manager
    id<EMOobNotificationManager> oobNotificationManager = [oobManager oobNotificationManagerWithClientId:clientCode];
    
    //Delete Existing Profile
    [oobNotificationManager clearNotificationProfilesWithCompletionHandler:^(id<EMOobResponse> aResponse, NSError
                                                                             *error) {
        
        if ([aResponse resultCode] == EMOobResultCodeSuccess)
        {
            self.scrollText.text = [@"\n\nNotification Profile Cleared!" stringByAppendingString:self.scrollText.text];
            [self didUnRegister];
        } else {
            self.scrollText.text = [[@"\n\nSomer Error Occured while deleting Notification Profile! " stringByAppendingFormat:@"%@",error]stringByAppendingString:self.scrollText.text];
            [self hideSpinner];
        } }];
}

@end
