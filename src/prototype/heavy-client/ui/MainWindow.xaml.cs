using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Text;
using System.Text.RegularExpressions;
using System.Timers;

namespace InterfaceGraphique_ClientLourd
{
    public partial class MainWindow : Window
    {
        const string chatTextBoxLabel = "Entrez votre message ici";
        System.Windows.Threading.DispatcherTimer dispatcherTimer;
        bool timerEnded = false;
        bool uniqueUser = false;
        string username;

        public MainWindow()
        {
            InitializeComponent();
            switchScreen(this);
            showLoginScreen();

            dispatcherTimer = new System.Windows.Threading.DispatcherTimer();
            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 10);
        }

        private void connectButton_Click(object sender, RoutedEventArgs e)
        {
            username_label_warning.Visibility = Visibility.Collapsed;
            ipAdresse_label_warning.Visibility = Visibility.Collapsed;
            port_Label_Warning.Visibility = Visibility.Collapsed;

            if (username_textbox.Text.Equals(""))
            {
                username_label_warning.Visibility = Visibility.Visible;
                username_label_warning.Content = "Veuillez entrer votre nom d'utilisateur.";
            }
            else if (ipAdresse_textBox.Text.Equals(""))
            {
                ipAdresse_label_warning.Visibility = Visibility.Visible;
                ipAdresse_label_warning.Content = "Veuillez entrer un adresse IP.";
            }
            else if (port_textBox.Text.Equals(""))
            {
                port_Label_Warning.Visibility = Visibility.Visible;
                port_Label_Warning.Content = "Veuillez entrer un numéro de port.";
            }
            else
            {
                username_label_warning.Visibility = Visibility.Collapsed;
                ipAdresse_label_warning.Visibility = Visibility.Collapsed;
                port_Label_Warning.Visibility = Visibility.Collapsed;

                FonctionNative.startConnection(ipAdresse_textBox.Text, port_textBox.Text);
                while (!FonctionNative.verifyConnection() && !timerEnded)
                {
                    startTimer(5000);
                }
                timerEnded = false;
                if (FonctionNative.verifyConnection())
                {
                    //Connection
                    FonctionNative.sendMessage("u" + username_textbox.Text);
                    startTimer(5000);
                    while (!uniqueUser && !timerEnded)
                    {
                        checkForMessage();
                    }
                    timerEnded = false;
                    if (uniqueUser)
                    {
                        dispatcherTimer.Start();
                        username = username_textbox.Text;
                        switchScreen(this);
                        showChatScreen();

                        username_textbox.Text = "";
                        ipAdresse_textBox.Text = "";
                        port_textBox.Text = "";
                    }
                    else
                    {
                        FonctionNative.stopConnection();
                        username_textbox.Text = "";
                        username_label_warning.Visibility = Visibility.Visible;
                        username_label_warning.Content = "Nom d'utilisateur déjà utilisé";
                    }
                } else
                {
                    //N'est pas connecter
                    ipAdresse_label_warning.Visibility = Visibility.Visible;
                    ipAdresse_label_warning.Content = "Échec de la connexion";
                }
            }
        }

        //Verify pour des nouveau message
        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            checkForMessage();
        }

        private void checkForMessage()
        {
            string message = FonctionNative.verifyForMessage();
            if (!message.Equals(""))
                dealWithMessage(message);
        }

        private void dealWithMessage(string message)
        {
            switch(message[0])
            {
                case 'r':
                    modifyUserList(message);
                    break;

                case 'm':
                    addToChat(message);
                    break;

                case 'a':
                    validateUser(message);
                    break;

                    //To cout erreur and check
                default:
                    addToChat(message);
                    break;
            }
                
        }

        private void modifyUserList(string message)
        {
            message = message.Substring(1);
            string[] users = message.Split(';');
            for (int i = 0; i < users.Length; i++)
                users_listBox.Items.Add(users[i]);
        }

        private void addToChat(string message)
        {
            message = message.Substring(1);
            //Get username
            int endOfUser = message.IndexOf(';');
            string user = message.Substring(0, endOfUser);
            //Get Date and Time
            message = message.Substring(endOfUser + 1);
            int endOfDate = message.IndexOf(';');
            string dateTime = message.Substring(0, endOfDate);
            //Rebuild Message
            message = message.Substring(endOfDate + 1);
            message = user + " a envoyé a " + dateTime + "\r\n" + message;

            chat_listBox.Items.Add(message);
            Border border = (Border)VisualTreeHelper.GetChild(chat_listBox, 0);
            ScrollViewer scrollViewer = (ScrollViewer)VisualTreeHelper.GetChild(border, 0);
            scrollViewer.ScrollToBottom();
        }

        private void startTimer(int durationInMS)
        {
            Timer t = new Timer();
            t.Interval = durationInMS; //In milliseconds here
            t.AutoReset = true; //Stops it from repeating
            t.Elapsed += new ElapsedEventHandler(TimerElapsed);
            t.Start();
        }

        private void TimerElapsed(object sender, ElapsedEventArgs e)
        {
            timerEnded = true;
        }

        private void validateUser(string message)
        {
            if (message.Equals("asuc"))
                uniqueUser = true;
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

            chat_listBox.Visibility = Visibility.Visible;
            chat_textBox.Visibility = Visibility.Visible;
            send_button.Visibility = Visibility.Visible;

            //Make sure every component is at the right place
            displayUserListChatMenuItem.Header = "Montrer les utilisateurs connecté";
            users_listBox.Visibility = Visibility.Collapsed;

            Grid.SetColumn(chat_listBox, 2);
            Grid.SetColumnSpan(chat_listBox, 3);

            Grid.SetColumn(chat_textBox, 2);
            Grid.SetColumnSpan(chat_textBox, 2);
        }

        private void leaveChatMenuItem_Click(object sender, RoutedEventArgs e)
        {
            FonctionNative.stopConnection();
            dispatcherTimer.Stop();

            uniqueUser = false;
            Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FFFFFF"));
            username = "";
            users_listBox.Items.Clear();
            chat_listBox.Items.Clear();

            switchScreen(this);
            showLoginScreen();
        }

        private void displayUserListChatMenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (users_listBox.Visibility.Equals(Visibility.Visible))
            {
                displayUserListChatMenuItem.Header = "Montrer les utilisateurs connecté";
                users_listBox.Visibility = Visibility.Collapsed;
               
                Grid.SetColumn(chat_listBox, 2);
                Grid.SetColumnSpan(chat_listBox, 3);

                Grid.SetColumn(chat_textBox, 2);
                Grid.SetColumnSpan(chat_textBox, 2);
            }
            else
            {
                displayUserListChatMenuItem.Header = "Cacher les utilisateur connecté";
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
                string message = username + ";" + DateTime.Now.ToString() + ";";
                FonctionNative.sendMessage("m" + message + chat_textBox.Text);

                chat_textBox.Text = "";
            }
        }

        private void chat_textBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
                send_button_Click(sender, e);
        }

        private void ApplicationColor_MenuTab_Click(object sender, RoutedEventArgs e)
        {
            ApplicationColorWindow applicationColorOptionWindow = new ApplicationColorWindow(this);
            var location = this.PointToScreen(new Point(0, 0));
            applicationColorOptionWindow.Left = location.X + this.Width - 20;
            applicationColorOptionWindow.Top = location.Y - 30;
            applicationColorOptionWindow.ShowDialog();
        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            FonctionNative.stopConnection();
        }

        private void username_textbox_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[A-zÀ-ÿ0-9._]+");
            e.Handled = !regex.IsMatch(e.Text);
        }

        private void TexteColor_MenuTab_Click(object sender, RoutedEventArgs e)
        {
            TextForeColorWindow applicationColorOptionWindow = new TextForeColorWindow(this);
            var location = this.PointToScreen(new Point(0, 0));
            applicationColorOptionWindow.Left = location.X + this.Width - 20;
            applicationColorOptionWindow.Top = location.Y - 30;
            applicationColorOptionWindow.ShowDialog();
        }

        private void BackgroundColor_MenuTab_Click(object sender, RoutedEventArgs e)
        {
            BackgroundColorWindow applicationColorOptionWindow = new BackgroundColorWindow(this);
            var location = this.PointToScreen(new Point(0, 0));
            applicationColorOptionWindow.Left = location.X + this.Width - 20;
            applicationColorOptionWindow.Top = location.Y - 30;
            applicationColorOptionWindow.ShowDialog();
        }
    }

    class FonctionNative
    {
        [DllImport("prototype-model.dll", CharSet = CharSet.Unicode)]
        public static extern void startConnection(string ipAdresse, string port);

        [DllImport("prototype-model.dll", CharSet = CharSet.Unicode)]
        public static extern void stopConnection();

        [DllImport("prototype-model.dll", CharSet = CharSet.Unicode)]
        public static extern void sendMessage(string data);

        [DllImport("prototype-model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool verifyConnection();

        [DllImport("prototype-model.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getQueueSize();

        [DllImport("prototype-model.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void verifyForMessage(StringBuilder str, int len);
        public static string verifyForMessage()
        {
            StringBuilder str = new StringBuilder(1024);
            verifyForMessage(str, str.Capacity);
            return str.ToString();
        }
    }
}