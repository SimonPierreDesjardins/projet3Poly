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
    let packetSender: PacketSender
    
    //var chatHistory: NSMutableArray = [String]
    
    init()
    {
        packetSender = PacketSender()
        packetSender.establishConnection()
        
    }
    
    deinit
    {
        packetSender.closeConnection()
    }
    
    func appendMessage(_ message: String)
    {
        //chatHistory.adding(message)
    }
    
    //func getChatHistory() -> NSMutableArray
    //{
      //  return chatHistory
    //}
    
}
