//
//  ChatUsersListViewController.swift
//  chatApp
//
//  Created by Philippe Marcotte on 2017-02-07.
//  Copyright © 2017 Philippe Marcotte. All rights reserved.
//

import UIKit

class ChatUsersListViewController: UIViewController, UITableViewDelegate, UITableViewDataSource
{
    var usersListTableView: UITableView!
    var chatUsersList: [String] = [String]()
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        usersListTableView = UITableView(frame: UIScreen.main.bounds, style: UITableViewStyle.plain)
        usersListTableView.delegate      =   self
        usersListTableView.dataSource    =   self
        usersListTableView.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
        self.view.addSubview(self.usersListTableView)
        usersListTableView.separatorStyle = .none
        //usersListTableView.frame = CGRect(x: 0, y: 0, width: usersListTableView.frame.size.width/2.0, height: usersListTableView.contentSize.height);
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int
    {
        return chatUsersList.count
        
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell
    {
        let cell:UITableViewCell=UITableViewCell(style: UITableViewCellStyle.subtitle, reuseIdentifier: "cell")
        cell.textLabel!.text = chatUsersList[indexPath.row]
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath)
    {
    }
}
