Example Project Application for iOS
===================================

1. Introduction

Ezio Mobile SDK Example is a sample iOS application designed to demonstrate
the basics of creating an iOS application based on the Ezio Mobile SDK.

The application demonstrates the following behaviour:
* Demonstrate the usage of Secure Pin Pad on iOS

2. Prerequisites

* Mac
* Xcode

3. Open and setup the project

In Xcode:
* File -> Open -> EzioMobileSdkSecureKeypadExample.xcodeproj
* Add the EzioMobile.framework in the project's "Link Binary with Libraries" list.

4. Configure the App

* In the file “EMViewController.m”, user can configure the Secure Pin Pad
by giving value onto two boolean variables “isScramblingEnabled” and 
“isDoublePassword”.

5. Run the Example App

* There are two text labels above the button on the first page, showing the
current configuration of Secure Pin Pad.
* To start using the Secure Pin Pad, just simply clicking the button 
“Show Single-Pin Keypad”.
* Users can enter their PINs by clicking the buttons on the Pinpad, and
click "OK" to finish entering and submit.
* Once "OK" be triggered, the Secure Pin Pad dismisses, and then the
example app will show a message to indicate there is a PIN object created
successfully. 


6. Notice
* For security purpose, all the pins obtained by using Secure Pin Pad are returned 
as SecureData objects, and the clear text pins are not able to be extracted from 
these SecureData objects.