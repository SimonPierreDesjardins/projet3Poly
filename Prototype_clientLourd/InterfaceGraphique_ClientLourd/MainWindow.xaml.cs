using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace InterfaceGraphique_ClientLourd
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            switchScreen(this);
            showLoginScreen();
        }

        private void connectButton_Click(object sender, RoutedEventArgs e)
        {
            switchScreen(this);
            showChatScreen();
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

        private void showChatScreen()
        {
            chat_menu.Visibility = Visibility.Visible;

            users_listBox.Visibility = Visibility.Visible;

            chat_listBox.Visibility = Visibility.Visible;
            chat_textBox.Visibility = Visibility.Visible;
            send_button.Visibility = Visibility.Visible;
        }

        private void leaveChatMenuItem_Click(object sender, RoutedEventArgs e)
        {
            switchScreen(this);
            showLoginScreen();
        }

        private void displayUserListChatMenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (users_listBox.Visibility.Equals(Visibility.Visible))
            {
                users_listBox.Visibility = Visibility.Collapsed;
                //chat_listBox.Width =  ActualWidth;
                //chat_listBox.HorizontalAlignment
                chat_listBox.Width = Width - 100;
                chat_listBox.Margin = new Thickness(0, 30, 0, 1);
                double i = this.ActualWidth;
                i = 0;
            }
            else
            {
                users_listBox.Visibility = Visibility.Visible;
                chat_listBox.Width = 2/3 * Grid.ActualWidth;
            }


        }

        /*
         * DoubleAnimation doubleAnimation = new DoubleAnimation();
            doubleAnimation.From = -tbmarquee.ActualWidth;
            doubleAnimation.To = canMain.ActualWidth;
            doubleAnimation.RepeatBehavior = RepeatBehavior.Forever;
            doubleAnimation.Duration = new Duration(TimeSpan.Parse("0 : 0 : 10"));
            tbmarquee.BeginAnimation(Canvas.LeftProperty, doubleAnimation);
            */
    }
}
