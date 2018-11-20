using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;

namespace tictactoe_gui
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {

        [DllImport(@"TICTACTOE.dll")]
        public static extern void init(char chessType);

        [DllImport(@"TICTACTOE.dll")]
        public static extern bool isValid(int row, int col);

        [DllImport(@"TICTACTOE.dll")]
        public static extern void human(int row, int col);

        [DllImport(@"TICTACTOE.dll")]
        public static extern void computer();

        [DllImport(@"TICTACTOE.dll")]
        public static extern int getComputerRow();

        [DllImport(@"TICTACTOE.dll")]
        public static extern int getComputerCol();

        [DllImport(@"TICTACTOE.dll")]
        public static extern void updateTurnAfterComputerTurn();

        [DllImport(@"TICTACTOE.dll")]
        public static extern int gameOver();

        private char xtype = 'X';
        private char otype = 'O';
        private char humanChessType;
        private char computerChessType;
        private bool isGameOver;

        public MainWindow()
        {
            InitializeComponent();
            humanChessType = xtype;
            computerChessType = otype;
            isGameOver = false;
            init(humanChessType);
            Button00.Click += new RoutedEventHandler(Button00_click);
            Button01.Click += new RoutedEventHandler(Button01_click);
            Button02.Click += new RoutedEventHandler(Button02_click);
            Button10.Click += new RoutedEventHandler(Button10_click);
            Button11.Click += new RoutedEventHandler(Button11_click);
            Button12.Click += new RoutedEventHandler(Button12_click);
            Button20.Click += new RoutedEventHandler(Button20_click);
            Button21.Click += new RoutedEventHandler(Button21_click);
            Button22.Click += new RoutedEventHandler(Button22_click);
        }

        private void Button00_click(object sender, RoutedEventArgs e) { click(0, 0); }
        private void Button01_click(object sender, RoutedEventArgs e) { click(0, 1); }
        private void Button02_click(object sender, RoutedEventArgs e) { click(0, 2); }
        private void Button10_click(object sender, RoutedEventArgs e) { click(1, 0); }
        private void Button11_click(object sender, RoutedEventArgs e) { click(1, 1); }
        private void Button12_click(object sender, RoutedEventArgs e) { click(1, 2); }
        private void Button20_click(object sender, RoutedEventArgs e) { click(2, 0); }
        private void Button21_click(object sender, RoutedEventArgs e) { click(2, 1); }
        private void Button22_click(object sender, RoutedEventArgs e) { click(2, 2); }

        private void click(int row, int col)
        {
            if (isGameOver) return;
            if (isValid(row, col))
            {               
                human(row, col);
                update(row, col, humanChessType);//update ui
                if(checkResult()) return;
                computer();
                int computerRow = getComputerRow();
                int computerCol = getComputerCol();
                update(computerRow, computerCol, computerChessType);//update ui
                updateTurnAfterComputerTurn();
                if (checkResult()) return;
            }
        }

        private void update(int row, int col, char chessType)
        {
            if (row == 0 && col == 0) { Button00.Content = chessType; }
            if (row == 0 && col == 1) { Button01.Content = chessType; }
            if (row == 0 && col == 2) { Button02.Content = chessType; }
            if (row == 1 && col == 0) { Button10.Content = chessType; }
            if (row == 1 && col == 1) { Button11.Content = chessType; }
            if (row == 1 && col == 2) { Button12.Content = chessType; }
            if (row == 2 && col == 0) { Button20.Content = chessType; }
            if (row == 2 && col == 1) { Button21.Content = chessType; }
            if (row == 2 && col == 2) { Button22.Content = chessType; }
        }

        private bool checkResult()
        {
            int result = gameOver();
            if (result == 0) return false;
            switch (result)
            {
                case 1:
                    {
                        MessageBox.Show("Computer Won!");
                        break;
                    }
                case 2:
                    {
                        MessageBox.Show("You Won!");
                        break;
                    }
                case 3:
                    {
                        MessageBox.Show("Draw!");
                        break;
                    }
            }
            isGameOver = true;
            return true;
        }
    }
}
