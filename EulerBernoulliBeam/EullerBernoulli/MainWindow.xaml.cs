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
using System.Windows.Threading;

namespace EullerBernoulli
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
		readonly double ScaleX = 10.0;
		readonly double ScaleY = 30;

		readonly Simulation m_sim = new Simulation();
		readonly DispatcherTimer m_timer = new DispatcherTimer();

		public MainWindow()
		{
			InitializeComponent();

			m_timer.Tick += Timer_Tick;
			m_timer.Interval = TimeSpan.FromMilliseconds(1000 / 10);
			m_timer.Start();
		}

		void Button_Click(object sender, RoutedEventArgs e)
		{
			Task.Run(() => m_sim.Start());
		}

		void Timer_Tick(object sender, EventArgs e)
		{
			var ws = m_sim.GetW();
			var scaled = new List<Point>(ws.Length);
			for (int i = 0; i < ws.Length; i++)
			{
				var pt = new Point(i * ScaleX, 160 - ws[i] * ScaleY);
				scaled.Add(pt);
			}

			lines.Points = new PointCollection(scaled);
			figure.StartPoint = scaled.First();
			lines.IsSmoothJoin = false;
		}
	}
}
