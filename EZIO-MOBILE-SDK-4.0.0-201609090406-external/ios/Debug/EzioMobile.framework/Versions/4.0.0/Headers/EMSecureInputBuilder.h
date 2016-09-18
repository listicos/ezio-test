/** -----------------------------------------------------------------------------
 
 Copyright (c) 2014  -  GEMALTO DEVELOPMENT - R&D
 
 -----------------------------------------------------------------------------
 GEMALTO MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 PARTICULAR PURPOSE, OR NON-INFRINGEMENT. GEMALTO SHALL NOT BE
 LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 
 THIS SOFTWARE IS NOT DESIGNED OR INTENDED FOR USE OR RESALE AS ON-LINE
 CONTROL EQUIPMENT IN HAZARDOUS ENVIRONMENTS REQUIRING FAIL-SAFE
 PERFORMANCE, SUCH AS IN THE OPERATION OF NUCLEAR FACILITIES, AIRCRAFT
 NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL, DIRECT LIFE
 SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH THE FAILURE OF THE
 SOFTWARE COULD LEAD DIRECTLY TO DEATH, PERSONAL INJURY, OR SEVERE
 PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH RISK ACTIVITIES"). GEMALTO
 SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR
 HIGH RISK ACTIVITIES.
 
 -----------------------------------------------------------------------------
 */

#import <UIKit/UIKit.h>

@protocol EMPinAuthInput;
@protocol EMSecureString;

// because appledoc does not support constants, all constants have been commented out
// in the comment block of an enumeration. Cross ref to this file has been added
// in EMSecureInputBuilder class.

/**
 Secure Input Builder constants :
 
 Callback blocks that need to be passed along as EMSecurePin objects when creating a new pinpad to receive events (Please take note that the clear text of passwords are not able to be extracted from EMSecurePin objects):
 
 typedef void (^EMSecurePinpadOnFinish)(id<EMSecurePin> firstPin, id<EMSecurePin> secondPin);
 
 Callback blocks that need to be passed along as EMSecureString objects when creating a new keypad to receive events:
 
 typedef void (^EMSecureKeypadOnFinish)(id<EMSecureString> firstData, id<EMSecureString> secondData);
 
 Macro to get UIColor from rgba value :
 
 #define EMUIColorFromRGBA(rgbaValue) [UIColor colorWithRed:((float)((rgbaValue & 0xFF000000) >> 24))/0xFF green:((float)((rgbaValue & 0x00FF0000) >> 16))/0xFF blue:((float)((rgbaValue & 0x00000FF00) >> 8))/0xFF alpha:((float)(rgbaValue & 0x0000000FF))/0xFF]
 
 Default encoding :
 
 #define EMSecureInputBuilder_DEFAULT_ENCODING NSUTF8StringEncoding
 
 Default scramble/unscramble :
 
 #define EMSecureInputBuilder_DEFAULT_SCRAMBLE_KEYBOARD YES
 
 Double password entry :
 
 #define EMSecureInputBuilder_DEFAULT_DOUBLE_PASSWORD_ENTRY_MODE NO
 
 Default character array :
 
 #define EMSecureInputBuilder_DEFAULT_CHARACTER_ARRAY  @"0123456789"
 
 Default button spacing :
 
 #define EMSecureInputBuilder_DEFAULT_BUTTON_SPACING 5
 Default number of columns
 
 #define EMSecureInputBuilder_DEFAULT_NO_OF_COLUMNS 4
 
 Default number of rows
 
 #define EMSecureInputBuilder_DEFAULT_NO_OF_ROWS 4
 
 Default screen background :
 
 #define EMSecureInputBuilder_DEFAULT_BACKGROUND_COLOR EMUIColorFromRGBA(0x3D1386FF)
 
 Button and button text colors :
 
 #define EMSecureInputBuilder_DEFAULT_CHARACTER_COLOR EMUIColorFromRGBA(0xD8E4E0FF)
 #define EMSecureInputBuilder_DEFAULT_CHARACTER_COLOR_SELECTED EMUIColorFromRGBA(0xE43673FF)
 #define EMSecureInputBuilder_DEFAULT_CHARACTER_COLOR_DISABLED EMUIColorFromRGBA(0x26028FFF)
 #define EMSecureInputBuilder_DEFAULT_BUTTON_GRADIENT_START EMUIColorFromRGBA(0xB6B6CCFF)
 #define EMSecureInputBuilder_DEFAULT_BUTTON_GRADIENT_END EMUIColorFromRGBA(0x63636DFF)
 #define EMSecureInputBuilder_DEFAULT_BUTTON_GRADIENT_SELECTED_START EMUIColorFromRGBA(0x11C18FFF)
 #define EMSecureInputBuilder_DEFAULT_BUTTON_GRADIENT_SELECTED_END EMUIColorFromRGBA(0xB0CAC3FF)
 #define EMSecureInputBuilder_DEFAULT_BUTTON_GRADIENT_DISABLED_START EMUIColorFromRGBA(0x5F6664FF)
 #define EMSecureInputBuilder_DEFAULT_BUTTON_GRADIENT_DISABLED_END EMUIColorFromRGBA(0x366256FF)
 
 Visible button press:
 
 #define EMSecureInputBuilder_DEFAULT_VISIBLE_BUTTON_PRESS YES
 
 Display texts :
 
 #define EMSecureInputBuilder_DEFAULT_TEXT_LABEL @"Enter your password."
 #define EMSecureInputBuilder_DEFAULT_SECOND_TEXT_LABEL @"Re-enter password."
 
 Input length :
 
 #define EMSecureInputBuilder_DEFAULT_TEXT_LABEL_COLOR EMUIColorFromRGBA(0xFFFFFFFF)
 #define EMSecureInputBuilder_DEFAULT_MINIMUM_INPUT_LENGTH 4
 #define EMSecureInputBuilder_DEFAULT_MAXIMUM_INPUT_LENGTH 8
 
 Default automatic enabled ok :
 
 #define EMSecureInputBuilder_DEFAULT_AUTOMATIC_ENABLED_OK YES
 
 Default automatic ok :
 
 #define EMSecureInputBuilder_DEFAULT_AUTOMATIC_OK NO
 
 Text border (focus and unfocus) :
 
 #define EMSecureInputBuilder_DEFAULT_TEXT_BORDER_FOCUS_COLOR EMUIColorFromRGBA(0xFF0066CC)
 #define EMSecureInputBuilder_DEFAULT_TEXT_BORDER_UNFOCUS_COLOR EMUIColorFromRGBA(0xFFA9A9A9)
 
 Default font :
 
 #define EMSecureInputBuilder_DEFAULT_TEXT_FONT_NAME @"ArialMT"
 #define EMSecureInputBuilder_DEFAULT_TEXT_FONT_SIZE 30
 
 Default delete key name :
 
 #define EMSecureInputBuilder_DEFAULT_DELETE_KEY_NAME @"⌫"
 
 Back button :
 
 #define EMSecureInputBuilder_DEFAULT_BACK_BUTTON_NAME @"Back"
 
 @since 2.5
 */
typedef NS_ENUM(NSInteger, EMSecureInputBuilder) {
    
    /// Dummy enumeration declaration to include the constants for API doc.
    EMSecureInputBuilder_DEFAULT = 0
};

/**
 <p>This callback method will return first and second pin</p>
 <p>And please take note that the clear text of passwords are not able to be extracted from EMSecurePin objects in callback.</p>
 <ul>
 <li><code>firstPin</code> The first (default) pin that user entered. In the single-data mode, this is the only variable that would be returned.</li>
 <li><code>secondPin</code> In the double-data mode, this pin is returned along with the firstPin. Note that there is NO guarantee that the two pins entered are the same.</li>
 </ul>
 */
typedef void (^EMSecurePinpadOnFinish)(id<EMPinAuthInput> firstPin, id<EMPinAuthInput> secondPin);

/**
 This callback method will return first and second data<p>
 <ul>
 <li><code>firstData</code> The first (default) data that user entered. In the single-data mode, this is the only variable that would be returned.</li>
 <li><code>secondData</code> In the double-data mode, this data is returned along with the firstData. Note that there is NO guarantee that the two data entered are the same.</li>
 </ul>
 */
typedef void (^EMSecureKeypadOnFinish)(id<EMSecureString> firstData, id<EMSecureString> secondData);

#define EMUIColorFromRGBA(rgbaValue) [UIColor colorWithRed:((float)((rgbaValue & 0xFF000000) >> 24))/0xFF green:((float)((rgbaValue & 0x00FF0000) >> 16))/0xFF blue:((float)((rgbaValue & 0x00000FF00) >> 8))/0xFF alpha:((float)(rgbaValue & 0x0000000FF))/0xFF]
#define EMSecurePinpadBuilder_DEFAULT_ENCODING                        NSUTF8StringEncoding
#define EMSecurePinpadBuilder_DEFAULT_SCRAMBLE_KEYBOARD               YES
#define EMSecurePinpadBuilder_DEFAULT_DOUBLE_PASSWORD_ENTRY_MODE      NO
#define EMSecurePinpadBuilder_DEFAULT_CHARACTER_ARRAY                 @"0123456789"
#define EMSecurePinpadBuilder_DEFAULT_BUTTON_SPACING                  5
#define EMSecurePinpadBuilder_DEFAULT_NO_OF_COLUMNS                   4
#define EMSecurePinpadBuilder_DEFAULT_NO_OF_ROWS                      4
#define EMSecurePinpadBuilder_DEFAULT_BACKGROUND_COLOR                EMUIColorFromRGBA(0x3D1386FF)
#define EMSecurePinpadBuilder_DEFAULT_CHARACTER_COLOR                 EMUIColorFromRGBA(0xD8E4E0FF)
#define EMSecurePinpadBuilder_DEFAULT_CHARACTER_COLOR_SELECTED        EMUIColorFromRGBA(0xE43673FF)
#define EMSecurePinpadBuilder_DEFAULT_CHARACTER_COLOR_DISABLED        EMUIColorFromRGBA(0x26028FFF)
#define EMSecurePinpadBuilder_DEFAULT_BUTTON_GRADIENT_START           EMUIColorFromRGBA(0xB6B6CCFF)
#define EMSecurePinpadBuilder_DEFAULT_BUTTON_GRADIENT_END             EMUIColorFromRGBA(0x63636DFF)
#define EMSecurePinpadBuilder_DEFAULT_BUTTON_GRADIENT_SELECTED_START  EMUIColorFromRGBA(0x11C18FFF)
#define EMSecurePinpadBuilder_DEFAULT_BUTTON_GRADIENT_SELECTED_END    EMUIColorFromRGBA(0xB0CAC3FF)
#define EMSecurePinpadBuilder_DEFAULT_BUTTON_GRADIENT_DISABLED_START  EMUIColorFromRGBA(0x5F6664FF)
#define EMSecurePinpadBuilder_DEFAULT_BUTTON_GRADIENT_DISABLED_END    EMUIColorFromRGBA(0x366256FF)
#define EMSecurePinpadBuilder_DEFAULT_VISIBLE_BUTTON_PRESS             YES
#define EMSecurePinpadBuilder_DEFAULT_TEXT_LABEL                      @"Enter your password."
#define EMSecurePinpadBuilder_DEFAULT_SECOND_TEXT_LABEL               @"Re-enter password."
#define EMSecurePinpadBuilder_DEFAULT_TEXT_LABEL_COLOR                EMUIColorFromRGBA(0xFFFFFFFF)
#define EMSecurePinpadBuilder_DEFAULT_MINIMUM_INPUT_LENGTH            4
#define EMSecurePinpadBuilder_DEFAULT_MAXIMUM_INPUT_LENGTH            8
#define EMSecurePinpadBuilder_DEFAULT_AUTOMATIC_ENABLED_OK            YES
#define EMSecurePinpadBuilder_DEFAULT_AUTOMATIC_OK                    NO
#define EMSecurePinpadBuilder_DEFAULT_TEXT_BORDER_FOCUS_COLOR         EMUIColorFromRGBA(0xFF0066CC)
#define EMSecurePinpadBuilder_DEFAULT_TEXT_BORDER_UNFOCUS_COLOR       EMUIColorFromRGBA(0xFFA9A9A9)
#define EMSecurePinpadBuilder_DEFAULT_TEXT_FONT_NAME                  @"ArialMT"
#define EMSecurePinpadBuilder_DEFAULT_TEXT_FONT_SIZE                  30
#define EMSecurePinpadBuilder_DEFAULT_DELETE_KEY_NAME                 @"⌫"
#define EMSecurePinpadBuilder_DEFAULT_BACK_BUTTON_NAME                @"Back"

/**
 The input builder class that enables to build a secure pinpad and keypad. <p>
 The secure pinpad/keypad does not use any native UIKit keypad but rather draws a custom the UI on the view itself. The use of `NSString` is limited to minimum to make sure pinpad and keypad has total control of wiping sensitive data after it is used. <p>
 */
@protocol EMSecureInputBuilder <NSObject>

#pragma mark Builder

/**
 @brief Creates a Secure Pinpad UIViewController. <p>
 @warning This method should be called once all the necessary configurations have been done. Note that the default configuration shall be applied for attributes that have not been set to custom values.
 @param isScrambling Indicates if the pinpad would have a scrambled key locations. The scrambling is completely random and different for each time the pinpad is shown.
 @param isDoublePin Indicates if the pinpad would have two text fields to enter the pin. This is useful in case of using the pinpad for a new password and its confirmation. It's important to be aware that the pinpad itself will NOT perform any comparison of the two pins. The application developer can use method [EMSecureContainer isEqual:] for an equality confirmation.
 @param pinEnteredBlock Callback block upon the OK button hit on the pinpad.
 @see EMSecureInputBuilder for the default configurations of the pinpad.
 @return UIViewController that holds the pinpad. This can be fed into a navigation controller or presented as a modal view controller in the current view.
 @since 2.5
 */
- (UIViewController*) buildWithScrambling:(BOOL)isScrambling doublePin:(BOOL)isDoublePin onFinishBlock:(EMSecurePinpadOnFinish)pinEnteredBlock;

#pragma mark Encoding

/**
 Sets the encoding to use when creating the EMSecurePin object from the text-based pin. <p/>
 @warning This method is especially dedicated for existing applications that are currently using their own keypad and would like to use EZIO keypad in replacement. For those applications, the EMSecurePin used to be generated from a NSString object given an encoding method. So, the application developers need to make sure to use the same (or compatible) encoding method to allow the generated bytes are correct.
 @param encoding The encoding method to use when generating byte array from the character password.
 @since 2.5
 */
- (void) setEncoding:(NSStringEncoding)encoding;

#pragma mark Cleanup

/**
 Wipes all the sensitive data of the pinpad builder. The method would also be automatically triggered upon the release of this object on the autorelease pool of the current thread.
 <p/>
 It's recommended to call this method at the end of the callback block `EMSecurePinpadOnFinish`. See definition of `EMSecurePinpadOnFinish` above. <br>
 <b>Note:</b> Other non-sensitive configuration such as color setting and text-label setting won't be reset in this function.
 @since 2.5
 */
- (void) wipe;

#pragma mark Pinpad Configuration

/**
 Sets the character array, extracted from the passed-by string of characters.
 <b>IMPORTANT</b>: At present, only digit characters (0 -> 9) are supported. Passing in any other characters would cause an NSException.
 @param charArr String of character array to be used to display on the pinpad.
 @since 2.5
 */
- (void) setCharacterArray:(NSString *)charArr;

/**
 Sets the preferred number of rows. The on-display number of rows depend on the number of characters in the character array and some other configurations. Refer to Programmer's Guide for the accepted range of values.
 @param numOfRows Preferred number of rows to display.
 @since 2.5
 */
- (void) setNumberOfRows:(int)numOfRows;

/**
 Sets the preferred number of columns. The on-display number of columns depend on the number of characters in the character array and some other configurations. Refer to Programmer's Guide for the accepted range of values.
 @param numOfCols Preferred number of columns to display.
 @since 2.5
 */
- (void) setNumberOfColumns:(int)numOfCols;

/**
 Setes the minimum input length. Refer to Programmer's Guide for the accepted range of values.
 @param minLen The pinpad would make sure the user has entered at least minLen characters before he/she can hit OK.
 @since 2.5
 */
- (void) setMinimumInputLength:(int)minLen;

/**
 Sets the maximum input length. Refer to Programmer's Guide for the accepted range of values.
 @param maxLen The pinpad would make sure the user cannot enter more than maxLen number of characters.
 @since 2.5
 */
- (void) setMaximumInputLength:(int)maxLen;

#pragma mark Display Texts

/**
 Sets the pin's text label.
 @param text Text string to be set. There is no specific check on the length of the text, but the text field stretches across the width of the screen.
 @since 2.5
 */
- (void) setTextLabel:(NSString *)text;

/**
 Sets the second pin input's text label.<p>
 This attribute is useful only in double-password mode where there are two input fields to enter the pins.
 @param text Text string to be set. There is no specific check on the length of the text, but the text field stretches across the width of the screen.
 @since 2.5
 */
- (void) setSecondTextLabel:(NSString *)text;

/**
 Sets the pin's text label's color. This value is used for both first and second pin input labels.
 @param color Color to set for the pin's text labels.
 @since 2.5
 */
- (void) setLabelTextColor:(UIColor*)color;

#pragma mark Look & Feel

/**
 Sets the spacing between the keys on the screen. Refer to Programmer's Guide for the accepted range of values.
 @param buttonSpacing The distance between the keys in terms of pixels.
 @since 2.5
 */
- (void) setButtonSpacing:(int)buttonSpacing;

/**
 Sets the background color of the pinpad's screen.
 @param backgroundColor Color to set for the background.
 @since 2.5
 */
- (void) setScreenBackgroundColor:(UIColor*)backgroundColor;

/**
 Sets the key's character color when it's being displayed (normal condition).
 @param color Color to set for the key's character in normal condition.
 @since 2.5
 */
- (void) setButtonCharacterColorNormal:(UIColor*)color;

/**
 Sets the key's character color when it's tapped (selected condition).<p>
 @param color Color to set for the key's character in selected condition.
 @since 2.5
 */
- (void) setButtonCharacterColorSelected:(UIColor*)color;

/**
 Sets the key's character color when it's disabled (disabled condition). This color is typically used for function keys such as Ok or Delete buttons.<p>
 @param color Color to set for the key's character in disabled condition.
 @since 2.5
 */
- (void) setButtonCharacterColorDisabled:(UIColor*)color;

/**
 Sets the key's background gradient starting color when it's being displayed (normal condition).<p>
 @param color Color to set for the key's background gradient start in normal condition.
 @since 2.5
 */
- (void) setButtonGradientNormalStart:(UIColor*)color;

/**
 Sets the key's background gradient ending color when it's being displayed (normal condition).<p>
 @param color Color to set for the key's background gradient end in normal condition.
 @since 2.5
 */
- (void) setButtonGradientNormalEnd:(UIColor*)color;

/**
 Sets the key's background gradient starting color when it's tapped (selected condition).<p>
 @param color Color to set for the key's background gradient start in selected condition.
 @since 2.5
 */
- (void) setButtonGradientSelectedStart:(UIColor*)color;

/**
 Sets the key's background gradient ending color when it's tapped (selected condition).<p>
 @param color Color to set for the key's background gradient end in selected condition.
 @since 2.5
 */
- (void) setButtonGradientSelectedEnd:(UIColor*)color;

/**
 Sets the key's background gradient starting color when it's disabled (disabled condition). This color is typically used for function keys such as Ok or Delete buttons.<p>
 @param color Color to set for the key's background gradient start in disabled condition.
 @since 2.5
 */
- (void) setButtonGradientDisabledStart:(UIColor*)color;

/**
 Sets the key's background gradient ending color when it's disabled (disabled condition). This color is typically used for function keys such as Ok or Delete buttons.<p>
 @param color Color to set for the key's background gradient end in disabled condition.
 @since 2.5
 */
- (void) setButtonGradientDisabledEnd:(UIColor*)color;

/**
 Sets the key's text border color when it's unfocussed (unselected condition).<p>
 @param color Color to set key's text border color when it's unfocussed.
 @since 2.6
 */
- (void) setTextBoxBorderUnFocussedColor:(UIColor*)color;

/**
 Sets the key's text border color when it's focussed (selected condition).<p>
 @param color Color to set key's text border color when it's focussed.
 @since 2.6
 */
- (void) setTextBoxBorderFocussedColor:(UIColor*)color;

/**
 Sets the if the button would be highlighted upon pressed.
 @param isVisible `YES` to highlight the button upon pressed, `NO` otherwise.
 */
- (void) setVisibleButtonPress:(BOOL)isVisible;

#pragma mark OK button

/**
 Enable this attribute to have the effect that the OK button is only enabled when minimum number of characters have been entered by the user.
 @param autoEnabled `YES` to indicate the OK button shall be disabled and enabled automatically by the library according to the number of characters input by user. `NO` to indicate the OK button shall always be enabled.
 @since 2.5
 */
- (void) setAutomaticEnabledOk:(BOOL)autoEnabled;

/**
 @brief Allows to automatically call OK button clicked event.
 
 When set on, the library would trigger the Ok button clicked automatically when the following conditions have been met:
 - The minimum and maximum input length are configured to be the same (see setMinimumInputLength: and setMaximumInputLength:).
 - User has entered up to the maximum number of characters needed.
 @param autoTriggered `YES` to enable the OK button to be triggered when the conditions are met. `NO` to disable this behavior.
 @since 2.5
 */
- (void) setAutomaticOk:(BOOL)autoTriggered;

@end
