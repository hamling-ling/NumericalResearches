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

namespace RotationalMotion
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
		PekoEngineNet.PekoEngineNet pe = new PekoEngineNet.PekoEngineNet();

		readonly DispatcherTimer timer = new DispatcherTimer();

		readonly List<Point> points = new List<Point>();

		readonly double scale = 20.0;

		public MainWindow()
		{
			InitializeComponent();

			pe.Initialize();

			timer.Tick += timer_Tick;
			timer.Interval = TimeSpan.FromMilliseconds(1000 / 10);
			timer.Start();

			for (int i = 0; i < 32; i++)
			{
				points.Add(new Point());
			}
		}

		void Button_Click(object sender, RoutedEventArgs e)
		{
			pe.Start();
		}

		void timer_Tick(object sender, EventArgs e)
		{
			if (!IsLoaded)
				return;

			var sln = pe.GetSolution(100);

			TimeOutput.Text = sln.t.ToString("F2");

			var scaled = new List<Point>(sln.points.Count());
			for (int i = 0; i < sln.points.Count(); i++)
			{
				var nonscaled = (Point)sln.points[i];
				scaled.Add(new Point(nonscaled.X * scale, 160 - nonscaled.Y * scale));
			}
			scaled.Add(scaled.First());
			figure.StartPoint = scaled.First();

			lines.Points = new PointCollection(scaled);
			lines.IsSmoothJoin = false;
		}
	}

	public static class Utility
	{
		public static double ToDeg(this double value)
		{
			return value / Math.PI * 180.0;
		}
	}
}
