//
//  ChatViewController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-17.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController


class ChatViewController: JSQMessagesViewController, JSQMessagesCollectionViewCellDelegate
{

    var chatHistory: Array = [JSQMessage]()
    
    let textCellIdentifier: NSString = "chatCell"
    
    lazy var outgoingBubbleImageView: JSQMessagesBubbleImage = self.setupOutgoingBubble()
    lazy var incomingBubbleImageView: JSQMessagesBubbleImage = self.setupIncomingBubble()
    
    private var cellsThatHaveBeenTapped = Set<NSInteger>()

    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
     
        self.title = "HEYO";
        
        self.showLoadEarlierMessagesHeader = true;
        
        self.senderId = "Moi"
        
        self.senderDisplayName = "P"
        
        // No avatars
        collectionView!.collectionViewLayout.incomingAvatarViewSize = CGSize.zero
        collectionView!.collectionViewLayout.outgoingAvatarViewSize = CGSize.zero
        
        self.inputToolbar.contentView.leftBarButtonItem = nil
        
        setupNavigationBarButton()
        
        receiveMessagePressed()
        
        
        automaticallyScrollsToMostRecentMessage = true
        
        self.collectionView?.reloadData()
        self.collectionView?.layoutIfNeeded()
    }
    
    func setupNavigationBarButton() {
        let backButton = UIBarButtonItem(title: "Back", style: UIBarButtonItemStyle.plain, target: self, action: #selector(backButtonTapped))
        navigationItem.leftBarButtonItem = backButton
        
        //create a new button
        let button: UIButton = UIButton(type: UIButtonType.custom)
        //set image for button
        button.setImage(UIImage(named: "./icons/ic_people_outline.png"), for: UIControlState.normal)
        //add function for button
        button.addTarget(self, action: #selector (backButtonTapped), for: UIControlEvents.touchUpInside)
        //set frame
        button.frame = CGRect(x: 0, y: 0, width: 53, height: 31)
        
        let barButton = UIBarButtonItem(customView: button)
        //assign button to navigationbar
        self.navigationItem.rightBarButtonItem = barButton
        //let infoButton = UIBarButtonItem(image: UIImage(named: "./icons/ic_people_outline.png"), style: UIBarButtonItemStyle.plain, target: self, action: #selector (backButtonTapped))
        //navigationItem.rightBarButtonItem = infoButton
        
    }
    
    func backButtonTapped() {
        dismiss(animated: true, completion: nil)
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
        let message = chatHistory[indexPath.item]
        if message.senderId == senderId
        {
            return outgoingBubbleImageView
        }
        else
        {
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
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout, heightForMessageBubbleTopLabelAt indexPath: IndexPath) -> CGFloat
    {
        let currentMessage = self.chatHistory[indexPath.item]
        
        if currentMessage.senderId == self.senderId
        {
            return 0.0
        }
        
        if indexPath.item - 1 > 0
        {
            let previousMessage = self.chatHistory[indexPath.item - 1]
            if previousMessage.senderId == currentMessage.senderId
            {
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
        if cellsThatHaveBeenTapped.contains(indexPath.row)
        {
            return kJSQMessagesCollectionViewCellLabelHeightDefault
        }
        
        return 0.0
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView!, didTapMessageBubbleAt indexPath: IndexPath!)
    {
        if cellsThatHaveBeenTapped.remove(indexPath.row) == nil
        {
            cellsThatHaveBeenTapped.insert(indexPath.row)
        }
        
        collectionView.reloadData()
    }
    
    func messagesCollectionViewCellDidTapMessageBubble(_ cell: JSQMessagesCollectionViewCell!) {
        
    }
    
    func messagesCollectionViewCellDidTap(_ cell: JSQMessagesCollectionViewCell!, atPosition position: CGPoint) {
        
    }
    
    func messagesCollectionViewCell(_ cell: JSQMessagesCollectionViewCell!, didPerformAction action: Selector!, withSender sender: Any!) {
        
    }
    
    func messagesCollectionViewCellDidTapAvatar(_ cell: JSQMessagesCollectionViewCell!) {
        
    }

}

