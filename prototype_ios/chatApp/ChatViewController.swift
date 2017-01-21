//
//  ViewController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-17.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController


class ChatViewController: JSQMessagesViewController {

    var chatHistoric = [JSQMessage]()
    
    let textCellIdentifier = "chatCell"
    
    let date = Date()
    
    let calendar = Calendar.current
    
    lazy var outgoingBubbleImageView: JSQMessagesBubbleImage = self.setupOutgoingBubble()
    lazy var incomingBubbleImageView: JSQMessagesBubbleImage = self.setupIncomingBubble()

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.senderId = "Moi"
        
        // No avatars
        collectionView!.collectionViewLayout.incomingAvatarViewSize = CGSize.zero
        collectionView!.collectionViewLayout.outgoingAvatarViewSize = CGSize.zero
        
        self.incomingMediaCellIdentifier = MessageViewIncoming.mediaCellReuseIdentifier();
        self.collectionView.register(MessageViewIncoming.nib(), forCellWithReuseIdentifier: self.incomingMediaCellIdentifier)
        self.outgoingMediaCellIdentifier = MessageViewOutgoing.mediaCellReuseIdentifier();
        self.collectionView.register(MessageViewOutgoing.nib(), forCellWithReuseIdentifier: self.outgoingMediaCellIdentifier)
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView!, messageDataForItemAt indexPath: IndexPath!) -> JSQMessageData! {
        return chatHistoric[indexPath.item]
    }
    
    override func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return chatHistoric.count
    }
    
    private func setupOutgoingBubble() -> JSQMessagesBubbleImage {
        let bubbleImageFactory = JSQMessagesBubbleImageFactory()
        return bubbleImageFactory!.outgoingMessagesBubbleImage(with: UIColor.jsq_messageBubbleBlue())
    }
    
    private func setupIncomingBubble() -> JSQMessagesBubbleImage {
        let bubbleImageFactory = JSQMessagesBubbleImageFactory()
        return bubbleImageFactory!.incomingMessagesBubbleImage(with: UIColor.jsq_messageBubbleLightGray())
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView!, messageBubbleImageDataForItemAt indexPath: IndexPath!) -> JSQMessageBubbleImageDataSource! {
        let message = chatHistoric[indexPath.item] // 1
        if message.senderId == senderId { // 2
            return outgoingBubbleImageView
        } else { // 3
            return incomingBubbleImageView
        }
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView!, avatarImageDataForItemAt indexPath: IndexPath!) -> JSQMessageAvatarImageDataSource! {
        return nil
    }
    
    override func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = super.collectionView(collectionView, cellForItemAt: indexPath) as! JSQMessagesCollectionViewCell
        let message = chatHistoric[indexPath.item]
        
        if message.senderId == self.senderId {
            
            let cell = super.collectionView(collectionView, cellForItemAt: indexPath) as! MessageViewOutgoing
            
            cell.timeLabel.text = DateFormatter().string(from: message.date)
            
        } else {
            
            let cell = super.collectionView(collectionView, cellForItemAt: indexPath) as! MessageViewIncoming
            
            cell.timeLabel.text = DateFormatter().string(from: message.date)
        }
        
        return cell
    }
    
    override func textViewDidChange(_ textView: UITextView) {
        super.textViewDidChange(textView)
        // If the text is not empty, the user is typing
        print(textView.text != "")
    }
}

