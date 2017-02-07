//
//  ChatDeleguator.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit

class ChatDelegator
{
    var chatManager: ChatManager
    var chatViewController: ChatViewController?
    
    init()
    {
        chatManager = ChatManager()
        NotificationCenter.default.addObserver(self, selector: #selector (ChatDelegator.onSendButtonTapped), name: .Chat_onSendButtonTapped, object: nil)
    }
    
    func getView() -> ChatViewController
    {
        chatViewController = chatViewController ?? ChatViewController()
        return chatViewController!
    }
    
    @objc func onSendButtonTapped(_ notification: NSNotification)
    {
        chatManager.appendMessage(notification.userInfo?["text"] as! String)
    }
    
}
