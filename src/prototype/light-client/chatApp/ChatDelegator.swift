//
//  ChatDeleguator.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController

class ChatDelegator
{
    var chatManager: ChatManager
    var chatViewController: ChatViewController?
    var connectionViewController: ConnectionViewController?
    
    init()
    {
        chatManager = ChatManager()
        NotificationCenter.default.addObserver(self, selector: #selector (self.onSendButtonTapped(_:)), name: .Chat_onSendButtonTapped, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector (self.onUsernameAuthentificationError), name: .Chat_onUsernameAuthentificationError, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector (self.onUsernameAuthentificationSuccess(_:)), name: .Chat_onUsernameAuthentificationSuccess, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector (self.onUsernameNeedVerification(_:)), name: .Chat_onUsernameNeedVerification, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector (self.onUsernameInvalid), name: .Chat_onUsernameInvalid, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector (self.updateViewControllerChatHistory), name: .Chat_onNewMessageReceived, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector (self.updateViewControllerUsersList), name: .Chat_onNewUser, object: nil)
    }
    
    func getChatViewController() -> ChatViewController
    {
        chatViewController = chatViewController ?? ChatViewController()
        updateViewControllerChatHistory()
        updateViewControllerUsersList()
        return chatViewController!
    }
    
    func setConnectionViewController(_ connectionViewController: ConnectionViewController)
    {
        self.connectionViewController = connectionViewController
        self.connectionViewController!.usernameMaxLength = chatManager.getUsernameMaxLength()
    }
    
    @objc func onSendButtonTapped(_ notification: NSNotification)
    {
        chatManager.sendMessage(notification.userInfo?["message"] as! JSQMessage)
        updateViewControllerChatHistory()
    }
    
    @objc func updateViewControllerChatHistory()
    {
        chatViewController!.updateChatHistory(chatManager.getChatHistory())
    }
    
    @objc func updateViewControllerUsersList()
    {
        chatViewController!.updateUsersList(chatManager.getUsersList())
    }
    
    @objc func onUsernameAuthentificationError()
    {
        connectionViewController?.showUsernameAlreadyUsedError()
    }
    
    @objc func onUsernameAuthentificationSuccess(_ notification: NSNotification)
    {
        self.chatViewController = getChatViewController()
        chatViewController!.senderDisplayName = notification.userInfo?["username"] as! String
        chatViewController!.senderId = notification.userInfo?["username"] as! String
        connectionViewController!.transitionView(viewToTransitionTo: chatViewController!)
    }
    
    @objc func onUsernameNeedVerification(_ notification: NSNotification)
    {
        if chatManager.establishConnection(ipAdress: notification.userInfo?["ipAdress"] as! String, port: notification.userInfo?["port"] as! String)
        {
            chatManager.verifyUsername(notification.userInfo?["username"] as! String)
        }
        else
        {
            connectionViewController!.showConnectionError()
        }
    }
    
    @objc func onUsernameInvalid()
    {
        connectionViewController!.showUsernameInvalidError()
    }
    
}
