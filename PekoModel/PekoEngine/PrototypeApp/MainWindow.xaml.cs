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

using PekoEngineNet;
using System.Windows.Threading;
using System.Diagnostics;

namespace PrototypeApp
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
		PekoEngineNet.PekoEngineNet pe = new PekoEngineNet.PekoEngineNet();

		DispatcherTimer timer = new DispatcherTimer();

		public MainWindow()
		{
			InitializeComponent();

			pe.Initialize();
			pe.Reset((float)(Math.PI * (1.5 / 2.0)), 0.0f);

			timer.Tick += timer_Tick;
			timer.Interval = TimeSpan.FromMilliseconds(1000 / 10);
			timer.Start();
		}

		private void Button_Click(object sender, RoutedEventArgs e)
		{
			pe.Start();
		}


		void timer_Tick(object sender, EventArgs e)
		{
			if (!IsLoaded)
				return;

			var sln = pe.GetSolution();
			Debug.WriteLine(sln.theta);
			Transform.Y = cv.Height - 50.0*sln.theta;
		}
	}
}
