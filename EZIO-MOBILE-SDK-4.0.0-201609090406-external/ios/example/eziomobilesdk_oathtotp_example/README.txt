Example Project Application for iOS
===================================

1. Introduction

Ezio Mobile SDK Example is a sample iOS application designed to demonstrate
the basics of creating an iOS application based on the Ezio Mobile SDK.

The application demonstrates the following behavior:
* Security guideline compliance of EzioMobileSDK_security_guideline.pdf.
* How to create a Token (requires a configured EPS).
* How to generate an OATH TOTP that can be verified by a server.

2. Prerequisites

* Mac
* Xcode

3. Setup and open the project

In Xcode:
* File -> Open -> EzioMobileSdkOathTotpExample.xcodeproj
* Add the EzioMobile.framework in the project's "Link Binary with Libraries" list.

4. Configure the App

The application will not work as provided.  It must first be setup to be
provisioned with the user credentials.  To enable this, perform the following
steps:
* Perform an "Allocate Application" operation in the EPS to get the PIN and
  registration code.  See Appendix for how to do this in a test environemnt.
* Edit FakeUI.m to add the PIN, registration code, etc.
* Edit FakeAppData.m to add your EPS settings, etc.
* Edit EMTlsConfiguration in Example.m if the security of the network
  connection needs to be lowered (e.g. using an http instead of https).

5. Run the Example App

The application prints the results of 3 tasks.
    1. Jailbreak detection - Check if the device is jailbroken. Abort app if jailbroken.
    2. Provisioning - Attempts to provisioning the device.
    3. Generate Otp - Generates an OATH TOTP for all available tokens.

---------------------------------------
Appendix

1. Security Guidelines

This project follows all relevant security guidelines established in the
EzioMobileSDK_security_guidelines.pdf document.  All guidelines followed are
commented inside the source code.  For project specific guidelines, the
following are followed:

* GEN05. No debug symbols

2. EPS 2.X Enroll Application

NOTE: This only serves as a quick reference.  See the EPS 2.X Integration
Guide for further details.

The following URL can be used to request the EPS to enroll the user with a new
device.  However, the following must be modified:
* The path up to 'https://localhost/" must be changed to point to your EPS.

https://localhost/enroller/api/enrollment/oath/enroll

The following XML payload must be sent as the data portion of the HTTP POST.
However, the following must be modified:
* userId - The name of the user to enroll
* userTokenId - The token ID (must be unique for the user)
* domain - The EPS domain for OATH TOTP
* key (see externalProvisioningMeta -> propertyEntry) - Additional provisioning
  information depending on the verification server.
  See the EPS 2.X Integration Guide for further details.
* value (see externalProvisioningMeta -> propertyEntry) - Additional
  provisioning information depending on the verification server.
  See the EPS 2.X Integration Guide for further details.

    <?xml version="1.0" encoding="UTF-8"?>
    <oathToken xmlns="http://gemalto.com/ezio/mobile/eps/api">
        <userId>TODO</userId>
        <userTokenId>TODO</userTokenId>
        <oathId>
            <manufacturerId>GA</manufacturerId>
            <tokenType>EM</tokenType>
        </oathId>
        <domain>TODO</domain>
        <activationDate>2012-12-31T15:23:59-08:00</activationDate>
        <expirationDate>2023-12-31T15:23:59-08:00</expirationDate>
        <activationState>ACTIVE</activationState>
        <externalProvisioningMeta>
            <propertyEntry>
                <key>TODO</key>
                <value>TODO</value>
            </propertyEntry>
        </externalProvisioningMeta>
    </oathToken>";

The "Content-Type" must be set to "application/xml"

The response will contain the PIN and registration code if successful.

Example:
    wget --header="Content-Type: application/xml" --post-data "<data>" <url> -O -
