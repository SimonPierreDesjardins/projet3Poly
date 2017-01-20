using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

//TODO: Enlever les users quand leave chat
//TODO: Faire leave chat un bouton séparé
//TODO: Remplacer "user" dans le timestamp

namespace InterfaceGraphique_ClientLourd
{
    public partial class MainWindow : Window
    {
        const string chatTextBoxLabel = "Enter your message here";

        public MainWindow()
        {
            InitializeComponent();
            switchScreen(this);
            showLoginScreen();
        }

        private void connectButton_Click(object sender, RoutedEventArgs e)
        {
            if (username_textbox.Text.Equals(""))
            {
                username_label_warning.Visibility = Visibility.Visible;
                username_label_warning.Content = "Please enter your username.";
            }
            else if (password_textbox.Password.Equals(""))
            {
                password_label_warning.Visibility = Visibility.Visible;
                password_label_warning.Content = "Please enter your username.";
            }
            else
            {
                //TODO: Verify the user is unique
                //TODO: Add connection to server here
               
                switchScreen(this);
                showChatScreen(username_textbox.Text);

                username_textbox.Text = "";
                password_textbox.Password = "";
            }
        }

        private void switchScreen(UIElement parent)
        {
            var childNumber = VisualTreeHelper.GetChildrenCount(Grid);

            for (var i = 0; i <= childNumber - 1; i++)
            {
                var uiElement = VisualTreeHelper.GetChild(Grid, i) as UIElement;
                uiElement.Visibility = Visibility.Collapsed;
            }
        }

        private void showLoginScreen()
        {
            username_label.Visibility = Visibility.Visible;
            username_textbox.Visibility = Visibility.Visible;
            username_label_warning.Visibility = Visibility.Collapsed;

            password_label.Visibility = Visibility.Visible;
            password_textbox.Visibility = Visibility.Visible;
            password_label_warning.Visibility = Visibility.Collapsed;

            ConnectButton.Visibility = Visibility.Visible;

            login_image.Visibility = Visibility.Visible;
        }

        private void showChatScreen(String username)
        {
            chat_menu.Visibility = Visibility.Visible;

            users_listBox.Visibility = Visibility.Visible;

            chat_listBox.Visibility = Visibility.Visible;
            chat_textBox.Visibility = Visibility.Visible;
            send_button.Visibility = Visibility.Visible;

            //Make sure every component is at the right place
            Grid.SetColumnSpan(chat_listBox, 2);
            Grid.SetColumn(chat_listBox, 3);

            Grid.SetColumn(chat_textBox, 3);
            Grid.SetColumnSpan(chat_textBox, 1);

            //Add user
            users_listBox.Items.Add(username);
        }

        private void leaveChatMenuItem_Click(object sender, RoutedEventArgs e)
        {
            switchScreen(this);
            showLoginScreen();

            //TODO: Disconnect from server here
        }

        private void displayUserListChatMenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (users_listBox.Visibility.Equals(Visibility.Visible))
            {
                displayUserListChatMenuItem.Header = "Show user list";
                users_listBox.Visibility = Visibility.Collapsed;
               
                Grid.SetColumn(chat_listBox, 2);
                Grid.SetColumnSpan(chat_listBox, 3);

                Grid.SetColumn(chat_textBox, 2);
                Grid.SetColumnSpan(chat_textBox, 2);

            }
            else
            {
                displayUserListChatMenuItem.Header = "Hide user list";
                users_listBox.Visibility = Visibility.Visible;
                
                Grid.SetColumnSpan(chat_listBox, 2);
                Grid.SetColumn(chat_listBox, 3);

                Grid.SetColumn(chat_textBox, 3);
                Grid.SetColumnSpan(chat_textBox, 1);
            }
        }

        private void chat_textBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (chat_textBox.Text == chatTextBoxLabel)
            {
                chat_textBox.Text = "";
            }
            chat_textBox.Foreground = Brushes.Black;
        }

        private void chat_textBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (chat_textBox.Text.Length == 0)
            {
                chat_textBox.Foreground = Brushes.Gray;
                chat_textBox.Text = chatTextBoxLabel;
            }
        }

        private void send_button_Click(object sender, RoutedEventArgs e)
        {
            bool isToolTip = chat_textBox.Text == chatTextBoxLabel;
            bool noContentInText = (chat_textBox.Text == "" || chat_textBox.Text.Replace(" ", "") == "");
            if (!isToolTip && !noContentInText)
            {
                string time = "User sent message at " + DateTime.Now.ToString();
                chat_listBox.Items.Add(time + "\r" + chat_textBox.Text);

                //Make scroll bar move to the bottom
                Border border = (Border)VisualTreeHelper.GetChild(chat_listBox, 0);
                ScrollViewer scrollViewer = (ScrollViewer)VisualTreeHelper.GetChild(border, 0);
                scrollViewer.ScrollToBottom();

                chat_textBox.Text = "";
            }
        }

        private void chat_textBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
                send_button_Click(sender, e);
        }

        private void chat_listBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Selector selector = sender as Selector;
            if (selector is ListBox)
            {
                (selector as ListBox).ScrollIntoView(selector.SelectedItem);
            }
        }
    }
}