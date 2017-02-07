using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;

//TODO: Finish color options

namespace InterfaceGraphique_ClientLourd
{
    public partial class MainWindow : Window
    {
        String username = "";
        const string chatTextBoxLabel = "Enter your message here";

        public MainWindow()
        {
            InitializeComponent();
            switchScreen(this);
            showLoginScreen();
        }

        private void connectButton_Click(object sender, RoutedEventArgs e)
        {
            username_label_warning.Visibility = Visibility.Collapsed;
            ipAdresse_label_warning.Visibility = Visibility.Collapsed;
            port_Label_Warning.Visibility = Visibility.Collapsed;


            if (username_textbox.Text.Equals(""))
            {
                username_label_warning.Visibility = Visibility.Visible;
                username_label_warning.Content = "Please enter your username.";
            }
            else if (ipAdresse_textBox.Text.Equals(""))
            {
                ipAdresse_label_warning.Visibility = Visibility.Visible;
                ipAdresse_label_warning.Content = "Please enter an ipAdresse.";
            }
            else if (port_textBox.Text.Equals(""))
            {
                port_Label_Warning.Visibility = Visibility.Visible;
                port_Label_Warning.Content = "Please enter a port number.";
            }
            else
            {
                //TODO: Verify the user is unique
                //TODO: Add connection to server here
                username = username_textbox.Text;
                FonctionNative.print_line(username_textbox.Text);

                switchScreen(this);
                showChatScreen();

                username_textbox.Text = "";
                ipAdresse_textBox.Text = "";
                port_textBox.Text = "";
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

            ipAdresse_label.Visibility = Visibility.Visible;
            ipAdresse_textBox.Visibility = Visibility.Visible;
            ipAdresse_label_warning.Visibility = Visibility.Collapsed;

            port_label.Visibility = Visibility.Visible;
            port_textBox.Visibility = Visibility.Visible;
            port_Label_Warning.Visibility = Visibility.Visible;

            ConnectButton.Visibility = Visibility.Visible;

            login_image.Visibility = Visibility.Visible;
        }

        private void showChatScreen()
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
            users_listBox.Items.Remove(username);
            chat_listBox.Items.Clear();

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
            //TODO: Build and Send paquet

            bool isToolTip = chat_textBox.Text == chatTextBoxLabel;
            bool noContentInText = (chat_textBox.Text == "" || chat_textBox.Text.Replace(" ", "") == "");
            if (!isToolTip && !noContentInText)
            {
                string time = username + " sent a message at " + DateTime.Now.ToString();
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

        private void ApplicationColor_MenuTab_Click(object sender, RoutedEventArgs e)
        {
            //TODO: fix spawning position. Check screen max pixels
            ApplicationColorWindow applicationColorOptionWindow = new ApplicationColorWindow(this);
            var location = this.PointToScreen(new Point(0, 0));
            applicationColorOptionWindow.Left = location.X + this.Width - 20;
            applicationColorOptionWindow.Top = location.Y - 30;
            applicationColorOptionWindow.ShowDialog();
        }
    }

    class FonctionNative
    {
        [DllImport("prototype-model.dll")]
        public static extern void print_line(string str);
    }
}