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
using System.Windows.Shapes;

namespace InterfaceGraphique_ClientLourd
{
    /// <summary>
    /// Interaction logic for ApplicationColorWindow.xaml
    /// </summary>
    public partial class TextForeColorWindow : Window
    {
        MainWindow parentWindow_;
        Brush parentTextColor_;

        public TextForeColorWindow(MainWindow window)
        {
            InitializeComponent();
            parentWindow_ = window;
            parentTextColor_ = parentWindow_.chat_listBox.Foreground;
        }

        private void applicationColorCanvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (applicationColorCanvas.SelectedColor != null)
            {
                parentWindow_.chat_listBox.Foreground = new SolidColorBrush(applicationColorCanvas.SelectedColor.Value);
                parentWindow_.users_listBox.Foreground = new SolidColorBrush(applicationColorCanvas.SelectedColor.Value);
                parentWindow_.chat_menu.Foreground = new SolidColorBrush(applicationColorCanvas.SelectedColor.Value);
                parentWindow_.chat_textBox.Foreground = new SolidColorBrush(applicationColorCanvas.SelectedColor.Value);
                parentWindow_.send_button.Foreground = new SolidColorBrush(applicationColorCanvas.SelectedColor.Value);
            }  
        }

        private void cancelButton_ApplicationColor_Click(object sender, RoutedEventArgs e)
        {
            parentWindow_.chat_listBox.Foreground = parentTextColor_;
            parentWindow_.users_listBox.Foreground = parentTextColor_;
            parentWindow_.chat_menu.Foreground = parentTextColor_;
            parentWindow_.chat_textBox.Foreground = parentTextColor_;
            parentWindow_.send_button.Foreground = parentTextColor_;
        }

        private void TextForeColorWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            parentWindow_.chat_listBox.Foreground = parentTextColor_;
            parentWindow_.users_listBox.Foreground = parentTextColor_;
            parentWindow_.chat_menu.Foreground = parentTextColor_;
            parentWindow_.chat_textBox.Foreground = parentTextColor_;
            parentWindow_.send_button.Foreground = parentTextColor_;
        }

        private void applyButton_ApplicationColor_Click(object sender, RoutedEventArgs e)
        {
            parentTextColor_ = parentWindow_.chat_listBox.Foreground;
            this.Close();
        }
    }
}
