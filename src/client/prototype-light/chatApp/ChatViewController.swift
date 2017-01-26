//
//  ChatViewController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-17.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController


class ChatViewController: JSQMessagesViewController, JSQMessagesComposerTextViewPasteDelegate
{

    var chatHistory = [JSQMessage]()
    
    let textCellIdentifier = "chatCell"
    
    lazy var outgoingBubbleImageView: JSQMessagesBubbleImage = self.setupOutgoingBubble()
    lazy var incomingBubbleImageView: JSQMessagesBubbleImage = self.setupIncomingBubble()

    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
     
        self.title = "HEYO";
        
        self.inputToolbar.contentView.textView.pasteDelegate = self;
        
        self.showLoadEarlierMessagesHeader = true;
        
        self.senderId = "Moi"
        
        // No avatars
        collectionView!.collectionViewLayout.incomingAvatarViewSize = CGSize.zero
        collectionView!.collectionViewLayout.outgoingAvatarViewSize = CGSize.zero
        
        self.inputToolbar.contentView.leftBarButtonItem = nil
        
        receiveMessagePressed()
    }
    
    func receiveMessagePressed() {
        let conversation = [JSQMessage(senderId: AvatarIdCook, displayName: getName(User.Cook), text: "What is this Black Majic?"),
        JSQMessage(senderId: AvatarIDSquires, displayName: getName(User.Squires), text: "It is simple, elegant, and easy to use. There are super sweet default settings, but you can customize like crazy"),
        JSQMessage(senderId: AvatarIdWoz, displayName: getName(User.Wozniak), text: "It even has data detectors. You can call me tonight. My cell number is 123-456-7890. My website is www.hexedbits.com."),
        JSQMessage(senderId: AvatarIdJobs, displayName: getName(User.Jobs), text: "JSQMessagesViewController is nearly an exact replica of the iOS Messages App. And perhaps, better."),
        JSQMessage(senderId: AvatarIDLeonard, displayName: getName(User.Leonard), text: "It is unit-tested, free, open-source, and documented."),
        JSQMessage(senderId: AvatarIDLeonard, displayName: getName(User.Leonard), text: "This is incredible"),
        JSQMessage(senderId: senderId!, displayName: getName(User.Wozniak), text: "I would have to agree"),
        JSQMessage(senderId: AvatarIDLeonard, displayName: getName(User.Leonard), text: "It is unit-tested, free, open-source, and documented like a boss."),
        JSQMessage(senderId: AvatarIdWoz, displayName: getName(User.Wozniak), text: "You guys need an award for this, I'll talk to my people at Apple. 💯 💯 💯")]
        
        for message in conversation
        {
            chatHistory.append(message!)
        }
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView!, messageDataForItemAt indexPath: IndexPath!) -> JSQMessageData!
    {
        return chatHistory[indexPath.item]
    }
    
    override func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int
    {
        return chatHistory.count
    }
    
    private func setupOutgoingBubble() -> JSQMessagesBubbleImage
    {
        let bubbleImageFactory = JSQMessagesBubbleImageFactory()
        return bubbleImageFactory!.outgoingMessagesBubbleImage(with: UIColor.jsq_messageBubbleBlue())
    }
    
    private func setupIncomingBubble() -> JSQMessagesBubbleImage
    {
        let bubbleImageFactory = JSQMessagesBubbleImageFactory()
        return bubbleImageFactory!.incomingMessagesBubbleImage(with: UIColor.jsq_messageBubbleLightGray())
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView!, messageBubbleImageDataForItemAt indexPath: IndexPath!) -> JSQMessageBubbleImageDataSource!
    {
        let message = chatHistory[indexPath.item] // 1
        if message.senderId == senderId { // 2
            return outgoingBubbleImageView
        } else { // 3
            return incomingBubbleImageView
        }
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView!, avatarImageDataForItemAt indexPath: IndexPath!) -> JSQMessageAvatarImageDataSource!
    {
        return nil
    }
    
    override func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell
    {
        let cell = super.collectionView(collectionView, cellForItemAt: indexPath) as! JSQMessagesCollectionViewCell
        
        let msg = self.chatHistory[indexPath.item]

            
        if msg.senderId == self.senderId {
            cell.textView.textColor = UIColor.white
        }
        else {
            cell.textView.textColor = UIColor.black
        }
        
        let attributes : [String:AnyObject] = [NSForegroundColorAttributeName:cell.textView.textColor!, NSUnderlineStyleAttributeName: NSUnderlineStyle.styleSingle.rawValue as AnyObject]
        cell.textView.linkTextAttributes = attributes
        
        return cell

    }
    
    override func didPressSend(_ button: UIButton!, withMessageText text: String!, senderId: String!, senderDisplayName: String!, date: Date!)
    {
        JSQSystemSoundPlayer.jsq_playMessageSentSound()
        
        let message = JSQMessage(senderId: senderId, senderDisplayName: senderDisplayName, date: date, text: text)
        
        self.chatHistory.append(message!)
        
        self.finishSendingMessage(animated: true)
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, attributedTextForMessageBubbleTopLabelAt indexPath: IndexPath) -> NSAttributedString?
    {
        let message = chatHistory[indexPath.item]
        
        if message.senderId == self.senderId {
            return nil
        }
        
        return NSAttributedString(string: message.senderDisplayName)
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout, heightForMessageBubbleTopLabelAt indexPath: IndexPath) -> CGFloat {
        let currentMessage = self.chatHistory[indexPath.item]
        
        if currentMessage.senderId == self.senderId {
            return 0.0
        }
        
        if indexPath.item - 1 > 0 {
            let previousMessage = self.chatHistory[indexPath.item - 1]
            if previousMessage.senderId == currentMessage.senderId {
                return 0.0
            }
        }
        
        return kJSQMessagesCollectionViewCellLabelHeightDefault;
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, attributedTextForCellTopLabelAt indexPath: IndexPath) -> NSAttributedString?
    {
        let message = self.chatHistory[indexPath.item]
        
        return JSQMessagesTimestampFormatter.shared().attributedTimestamp(for: message.date)
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout, heightForCellTopLabelAt indexPath: IndexPath) -> CGFloat
    {
        return kJSQMessagesCollectionViewCellLabelHeightDefault
    }
    
    func composerTextView(_ textView: JSQMessagesComposerTextView!, shouldPasteWithSender sender: Any!) -> Bool {
        if (UIPasteboard.general.image != nil) {
            // If there's an image in the pasteboard, construct a media item with that image and `send` it.
            
            let item = JSQPhotoMediaItem(image: UIPasteboard.general.image)
            
            let message = JSQMessage(senderId: self.senderId, senderDisplayName: self.senderDisplayName, date: NSDate() as Date!, media: item)
            self.chatHistory.append(message!)
            self.finishSendingMessage()
            
            return false
        }
        
        return true
    }
}

