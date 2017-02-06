//
//  ChatDeleguator.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit

class ChatDelegator : NSObject
{
    var chatManager: ChatManager
    override init()
    {
        chatManager = ChatManager()
    }


    func setUpObserver()
    {
        NotificationCenter.default.addObserver(self, selector: #selector (ChatDelegator.onSendButtonTapped), name: .Chat_onSendButtonTapped, object: nil)
    }
    
    func onSendButtonTapped(_ notification: NSNotification)
    {
        
    }
    
}
