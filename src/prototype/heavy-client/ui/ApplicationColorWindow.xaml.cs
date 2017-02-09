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
    public partial class ApplicationColorWindow : Window
    {
        MainWindow parentWindow_;
        Brush parentColor_;

        public ApplicationColorWindow(MainWindow window)
        {
            InitializeComponent();
            parentWindow_ = window;
            parentColor_ = parentWindow_.Background;
        }

        private void applicationColorCanvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (applicationColorCanvas.SelectedColor != null)
            {
                this.Background = new SolidColorBrush(applicationColorCanvas.SelectedColor.Value);
                parentWindow_.Background = new SolidColorBrush(applicationColorCanvas.SelectedColor.Value);
            }  
        }

        private void cancelButton_ApplicationColor_Click(object sender, RoutedEventArgs e)
        {
            this.Background = parentColor_;
            parentWindow_.Background = parentColor_;

            byte a = ((Color)parentColor_.GetValue(SolidColorBrush.ColorProperty)).A;
            byte g = ((Color)parentColor_.GetValue(SolidColorBrush.ColorProperty)).G;
            byte r = ((Color)parentColor_.GetValue(SolidColorBrush.ColorProperty)).R;
            byte b = ((Color)parentColor_.GetValue(SolidColorBrush.ColorProperty)).B;

            applicationColorCanvas.SelectedColor = Color.FromArgb(a, r, g, b);
        }

        private void ApplicationColorWindow1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            this.Background = parentColor_;
            parentWindow_.Background = parentColor_;
        }

        private void applyButton_ApplicationColor_Click(object sender, RoutedEventArgs e)
        {
            parentColor_ = this.Background;
            this.Close();
        }
    }
}
