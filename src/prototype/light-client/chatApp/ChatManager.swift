//
//  ChatManager.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//


class ChatManager
{
    let packetSender: PacketSender
    
    init()
    {
        packetSender = PacketSender()
        packetSender.establishConnection()
    }
    
    deinit
    {
        packetSender.closeConnection()
    }
    
    
}
