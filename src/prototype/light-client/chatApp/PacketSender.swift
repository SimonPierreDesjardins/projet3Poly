//
//  SocketIOManager.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import SwiftSocket

class PacketSender
{
    let client = TCPClient(address: "132.207.241.132", port: 5000)
    
    func establishConnection()
    {
        switch client.connect(timeout: 1) {
            case .success:
                print("yay")
                break
            case .failure(let error):
                print(error)
        }
    }
    
    func sendMessage(_ message: String)
    {
        switch client.send(string: message) {
        case .success:
            guard let data = client.read(1024*10) else { return }
            
            if let response = String(bytes: data, encoding: .utf8) {
                print(response)
            }
        case .failure(let error):
            print(error)
        }

    }
    
    func closeConnection()
    {
        client.close()
    }
}
