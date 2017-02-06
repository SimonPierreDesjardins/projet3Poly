//
//  SocketIOManager.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import SocketIO

class PacketSender
{
    let socket: SocketIOClient = SocketIOClient(socketURL: URL(string: "https://127.0.0.1:3000")!)
    
    func establishConnection()
    {
        socket.connect()
    }
    
    func closeConnection()
    {
        socket.disconnect()
    }
}
