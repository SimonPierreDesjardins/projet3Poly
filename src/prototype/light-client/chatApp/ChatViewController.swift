//
//  ChatViewController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-17.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit
import JSQMessagesViewController
import SideMenu

class ChatViewController: JSQMessagesViewController, UINavigationBarDelegate
{
    class ChatCollectionViewFlowLayout: JSQMessagesCollectionViewFlowLayout
    {
        override init()
        {
            super.init()
            self.messageBubbleLeftRightMargin = 0.0
        }
        
        required init?(coder aDecoder: NSCoder)
        {
            super.init(coder: aDecoder)
        }
    }
    
    var chatHistory = [JSQMessage]()
    
    lazy var outgoingBubbleImageView: JSQMessagesBubbleImage = self.setupOutgoingBubble()
    lazy var incomingBubbleImageView: JSQMessagesBubbleImage = self.setupIncomingBubble()
    
    private var cellsThatHaveBeenTapped = Set<NSInteger>()
    
    private var navigationBar: UINavigationBar = UINavigationBar(frame: CGRect(x: 0, y: 0, width: UIScreen.main.bounds.width, height: 69))
    
    private var usersListViewController = ChatUsersListViewController()
    
    let dateFormatter = DateFormatter()
    
    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        //let statusOpaqueBar: UINavigationBar = UINavigationBar(frame: CGRect(x:0, y:0, width: UIScreen.main.bounds.width, height: UIApplication.shared.statusBarFrame.height))
            
        //self.view.addSubview(statusOpaqueBar)
        
        //self.collectionView.collectionViewLayout = ChatCollectionViewFlowLayout()
               
        // No avatars
        collectionView!.collectionViewLayout.incomingAvatarViewSize = CGSize.zero
        collectionView!.collectionViewLayout.outgoingAvatarViewSize = CGSize.zero
        
        self.inputToolbar.contentView.leftBarButtonItem = nil
        
        setupSideMenu()
        
        setupNavigationBarButton()
        
        //receiveMessagePressed()
        
        self.topContentAdditionalInset = 50
        
        self.collectionView?.reloadData()
        self.collectionView?.layoutIfNeeded()
        
        dateFormatter.dateFormat = ("yyyy-MM-dd HH:mm:ss")
    }
    
    func updateUsersList(_ usersList: [String])
    {
        usersListViewController.chatUsersList = usersList
        if usersListViewController.usersListTableView != nil
        {
            usersListViewController.usersListTableView.reloadData()
        }
    }
    
    func updateChatHistory(_ chatHistory: [JSQMessage])
    {
        self.chatHistory = chatHistory
        if self.collectionView != nil
        {
            self.collectionView.reloadData()
        }
    }
    
    func setupSideMenu()
    {
        let menuRightNavigationController = UISideMenuNavigationController(rootViewController: usersListViewController)
        // UISideMenuNavigationController is a subclass of UINavigationController, so do any additional configuration
        // of it here like setting its viewControllers. If you're using storyboards, you'll want to do something like:
        // let menuRightNavigationController = storyboard!.instantiateViewController(withIdentifier: "RightMenuNavigationController") as! UISideMenuNavigationController
        SideMenuManager.menuRightNavigationController = menuRightNavigationController
        SideMenuManager.menuFadeStatusBar = false
    }
    
    func setupNavigationBarButton()
    {
        navigationBar.delegate = self;
        
        // Create a navigation item with a title
        let navigationItem = UINavigationItem()
        //navigationItem.title = self.senderDisplayName + " Chat"
        
        // Create left and right button for navigation item
        let leftButton =  UIBarButtonItem(title: "Retour", style:   UIBarButtonItemStyle.plain, target: self, action: #selector (backButtonTapped))
        let rightButton = UIBarButtonItem(image: UIImage(named: "./icons/ic_people_outline.png"), style: UIBarButtonItemStyle.plain, target: self, action: #selector (socialButtonTapped))
        
        // Create two buttons for the navigation item
        navigationItem.leftBarButtonItem = leftButton
        navigationItem.rightBarButtonItem = rightButton
        
        // Assign the navigation item to the navigation bar
        navigationBar.items = [navigationItem]
        
        // Make the navigation bar a subview of the current view controller
        self.view.addSubview(navigationBar)
    }
    
    func backButtonTapped()
    {
        dismiss(animated: true, completion: nil)
        NotificationCenter.default.post(name: .Chat_onExitChat, object: nil)
    }
    
    func socialButtonTapped()
    {
        present(SideMenuManager.menuRightNavigationController!, animated: true, completion: nil)
    }
    
    func receiveMessagePressed()
    {
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
            NotificationCenter.default.post(name: .Chat_onSendButtonTapped, object: nil, userInfo: ["message":message!])
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
            
        if msg.senderId == self.senderId
        {
            cell.textView.textColor = UIColor.white
        }
        else
        {
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
        
        self.finishSendingMessage(animated: true)
        
        NotificationCenter.default.post(name: .Chat_onSendButtonTapped, object: nil, userInfo: ["message":message!])
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
        
        return NSAttributedString(string: dateFormatter.string(from: message.date), attributes: JSQMessagesTimestampFormatter.shared().dateTextAttributes as! [String : Any]?)
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
}

