//
//  ConnexionController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-01-20.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit

class ConnectionController: UIViewController
{
    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var usernameTextBox: UITextField!
    @IBOutlet weak var bottomLayoutGuideConstraint: NSLayoutConstraint!
    
    var isKeyboardHidingComponent = false
    var keyboardHeight = CGFloat()
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        registerForKeyboardNotifications()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        deregisterFromKeyboardNotifications()
    }
    
    func registerForKeyboardNotifications()
    {
        //Adding notifies on keyboard appearing
        NotificationCenter.default.addObserver(self, selector: #selector(self.keyboardWasShown), name: NSNotification.Name.UIKeyboardWillShow, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(self.keyboardWillBeHidden), name: NSNotification.Name.UIKeyboardWillHide, object: nil)
    }
    
    
    func deregisterFromKeyboardNotifications()
    {
        //Removing notifies on keyboard appearing
        NotificationCenter.default.removeObserver(self, name: NSNotification.Name.UIKeyboardWillShow, object: nil)
        NotificationCenter.default.removeObserver(self, name: NSNotification.Name.UIKeyboardWillHide, object: nil)
    }
    
    func keyboardWasShown(notification: NSNotification)
    {
        //Need to calculate keyboard exact size due to Apple suggestions
        let info : NSDictionary = notification.userInfo! as NSDictionary
        let keyboardSize = (info[UIKeyboardFrameBeginUserInfoKey] as? NSValue)?.cgRectValue.size
        keyboardHeight = keyboardSize!.height
        
        var aRect : CGRect = self.view.frame
        aRect.size.height -= keyboardSize!.height
        isKeyboardHidingComponent = !aRect.contains(connectButton!.frame.origin)
        if (isKeyboardHidingComponent)
        {
            bottomLayoutGuideConstraint.constant += keyboardHeight
        }
        
    }
    
    func keyboardWillBeHidden(notification: NSNotification)
    {
        if (isKeyboardHidingComponent)
        {
            bottomLayoutGuideConstraint.constant -= keyboardHeight
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        super.prepare(for: segue, sender: sender)
        let chatContainerViewController = segue.destination as! ChatContainerViewController
        
        chatContainerViewController.senderDisplayName = usernameTextBox.text!
    }
}

