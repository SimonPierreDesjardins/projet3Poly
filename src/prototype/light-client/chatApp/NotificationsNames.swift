//
//  NotificationsNames.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import NotificationCenter

extension Notification.Name
{
    static let Chat_onSendButtonTapped: Notification.Name = Notification.Name("SendButtonClicked")
    static let Datagram_chatDatagramReceived: Notification.Name = Notification.Name("ChatDatagramReceived")
    static let Chat_onUsernameAuthentificationError: Notification.Name = Notification.Name("UsernameAlreadyUsed")
    static let Chat_onUsernameAuthentificationSuccess: Notification.Name = Notification.Name("UsernameCorrect")
    static let Chat_onUsernameNeedVerification: Notification.Name = Notification.Name("UsernameNeedVerification")
    static let Chat_onUsernameTooLong: Notification.Name = Notification.Name("UsernameTooLong")
    static let Chat_onUsernameInvalid: Notification.Name = Notification.Name("UsernameInvalid")
    static let Chat_onNewMessageReceived: Notification.Name = Notification.Name("NewMessageReceived")
    static let Chat_onNewUser: Notification.Name = Notification.Name("NewUser")
}
