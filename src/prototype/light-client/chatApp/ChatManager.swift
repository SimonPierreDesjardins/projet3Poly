//
//  ChatManager.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-01.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import Foundation
import JSQMessagesViewController

class ChatManager
{
    let datagramSender: DatagramSender
    
    var chatHistory : [JSQMessage]
    
    var username: String?
    
    var chatUsersList : [String]
    
    var ipAdress: String?
    
    var port: Int?
    
    let dateFormatter = DateFormatter()
    
    let sizeSeparator = ";"
    
    let sizeSeparatorUTF8 : UInt8
    
    init()
    {
        datagramSender = DatagramSender()
        chatHistory = [JSQMessage]()
        chatUsersList = [String]()
        dateFormatter.dateFormat = ("yyyy-MM-dd HH:mm:ss")
        sizeSeparatorUTF8 = sizeSeparator.utf8[sizeSeparator.utf8.startIndex]
        NotificationCenter.default.addObserver(self, selector: #selector (onChatDatagramReception), name: .Datagram_chatDatagramReceived, object: nil)
    }
    
    deinit
    {
        datagramSender.closeConnection()
    }
    
    func sendMessage(_ message: JSQMessage)
    {
        //appendMessage(message)
        datagramSender.sendMessage("m"+message.senderDisplayName+";"+dateFormatter.string(from: message.date)+";"+message.text!)
    }
    
    func appendMessage(_ message: JSQMessage)
    {
        lock(lock: chatHistory as AnyObject, execute:{ chatHistory.append(message) })
        NotificationCenter.default.post(name: .Chat_onNewMessageReceived, object: nil)
    }
    
    func appendExternalMessage( username: String, date: Date, text: String)
    {
        appendMessage(JSQMessage(senderId: username, senderDisplayName: username, date: date, text: text))
    }
    
    @objc func onChatDatagramReception(_ notification: NSNotification)
    {
        var data = notification.userInfo?["data"] as! [UInt8]
        
        while !data.isEmpty
        {
            let sizeEndPos: Int = data.index(of: sizeSeparatorUTF8)!
            
            let datagramSize: Int = Int(String(bytes: data[0..<sizeEndPos], encoding: .utf8)!)!
            
            let sizeEndAfterPos = sizeEndPos + 1
            
            let datagram: String = String(bytes: data[sizeEndAfterPos..<sizeEndAfterPos + datagramSize], encoding: .utf8)!
            
            data = [UInt8](data[(sizeEndAfterPos + datagramSize)..<data.count])
            
            let datagramHeader = datagram[datagram.startIndex]
            
            let contentIndex = datagram.index(after: datagram.startIndex)..<datagram.endIndex
            let datagramContent = datagram[contentIndex]
            
            switch datagramHeader
            {
                case "a":
                    usernameDatagramReader(datagramContent)
                    break
                case "m":
                    messageDatagramReader(datagramContent)
                    break
                case "r":
                    addUsersListDatagramReader(datagramContent)
                    break
                
                default:
                    print("Unknown type of datagram")
                    break
            }
        }
    }
    
    func deleteUsersFromListDatagramReader(_ datagramContent: String)
    {
        //self.chatUsersList.remove(at: datagramContent)
        NotificationCenter.default.post(name: .Chat_onUpdateUsers, object: nil)
    }
    
    func addUsersListDatagramReader(_ datagramContent: String)
    {
        chatUsersList = datagramContent.characters.split(separator: ";").map(String.init)
        
        NotificationCenter.default.post(name: .Chat_onUpdateUsers, object: nil)
    }
    
    func usernameDatagramReader(_ datagramContent: String)
    {
        if datagramContent == "suc"
        {
            NotificationCenter.default.post(name: .Chat_onUsernameAuthentificationSuccess, object: nil, userInfo: ["username":self.username!])
        }
        else if datagramContent == "err"
        {
            datagramSender.closeConnection()
            NotificationCenter.default.post(name: .Chat_onUsernameAuthentificationError, object: nil, userInfo: nil)
        }
    }
    
    func messageDatagramReader(_ datagramContent: String)
    {
        var content = datagramContent
        
        let usernameRange = content.range(of: ";")
        let username = content[content.startIndex..<(usernameRange?.lowerBound)!]
        
        content = content[(usernameRange?.upperBound)!..<content.endIndex]
        
        let dateRange = content.range(of: ";")
        let date: Date = dateFormatter.date(from: content[content.startIndex..<(dateRange?.lowerBound)!])!
        
        content = content[(dateRange?.upperBound)!..<content.endIndex]
        
        let text = content
        
        appendExternalMessage(username: username, date: date, text: text)
    }
    
    func getChatHistory() -> [JSQMessage]
    {
        return chatHistory
    }
    
    func verifyUsername(_ username: String)
    {
        let usernameRegex = "[A-zÀ-ÿ0-9._]+"
        let usernameTest = NSPredicate(format: "SELF MATCHES %@", usernameRegex)
        
        if !usernameTest.evaluate(with: username)
        {
            NotificationCenter.default.post(name: .Chat_onUsernameInvalid, object: nil, userInfo: nil)
            return
        }
        
        self.username = username
        
        datagramSender.sendMessage("u" + username)
    }
    
    func getUsernameMaxLength() -> Int
    {
        return 10
    }
    
    func getUsersList() -> [String]
    {
        return chatUsersList
    }
    
    func establishConnection(ipAdress: String, port: String) -> Bool
    {
        self.ipAdress = ipAdress
        guard let intPort = Int(port) else { return false }
        self.port = intPort
        return datagramSender.establishConnection(ipAdress: ipAdress, port: self.port!)
    }
    
    func closeConnection()
    {
        chatUsersList = [String]()
        chatHistory = [JSQMessage]()
        datagramSender.closeConnection()
    }
}
