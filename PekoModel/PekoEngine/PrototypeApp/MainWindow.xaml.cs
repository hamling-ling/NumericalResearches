using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Media;
using System.Windows.Threading;
using System.Linq;
using PekoEngineNet;

namespace PrototypeApp
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
		static readonly double kTheta = Math.PI / 2.0;

		PekoEngineNet.PekoEngineNet pe = new PekoEngineNet.PekoEngineNet();

		DispatcherTimer timer = new DispatcherTimer();

		readonly List<Point> points = new List<Point>();

		public MainWindow()
		{
			InitializeComponent();

			pe.Initialize();
			pe.Reset(Math.PI * 1.47 / 2.0, 0.0f);

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
			var theta_half_rad = (kTheta+sln.theta) / 2.0;
			var theta_half_deg = theta_half_rad.ToDeg();

			LeftArmRotateTransform.Angle = -theta_half_deg;
			RightArmRotateTransform.Angle = theta_half_deg;

			TimeOutput.Text = sln.t.ToString("F2");

			var pointpoints = sln.points.Cast<Point>();
			lines.Points = new PointCollection(pointpoints);
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
