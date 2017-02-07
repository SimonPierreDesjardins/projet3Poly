//
//  ChatManager.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import JSQMessagesViewController

class ChatManager
{
    let packetSender: DatagramSender
    
    var chatHistory : [String]
    
    init()
    {
        packetSender = DatagramSender()
        packetSender.establishConnection()
        chatHistory = [String]()
        NotificationCenter.default.addObserver(self, selector: #selector (onChatDatagramReception), name: .Datagram_chatDatagramReceived, object: nil)
    }
    
    deinit
    {
        packetSender.closeConnection()
    }
    
    func appendMessage(_ message: String)
    {
        lock(lock: chatHistory as AnyObject, execute:{ chatHistory.append(message) })
    }
    
    @objc func onChatDatagramReception(_ notification: NSNotification)
    {
        appendMessage(notification.userInfo?["Datagram"] as! String)
    }
    
    func getChatHistory() -> [String]
    {
        return chatHistory
    }
    
}
