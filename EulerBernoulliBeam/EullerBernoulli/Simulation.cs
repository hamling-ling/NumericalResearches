using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace EullerBernoulli
{
	public class Simulation
	{
		public const int N = 10;
		public const int TotN = N + 4;
		readonly double[] m_iniW = new double[TotN];// stores values(at t = 0)
		readonly double[] m_newW = new double[TotN];// stores values(at t = j+1)
		readonly double[] m_curW = new double[TotN];// current values (t=j)
		readonly double[] m_preW = new double[TotN];// old values (t=j-1)
		readonly double[] m_getW = new double[TotN];// values to show
		readonly ReaderWriterLock m_lock = new ReaderWriterLock();

		const double lambda = -0.001;
		const int LoopNum = 10000;

		public Simulation()
		{
			Array.Clear(m_iniW, 0, m_iniW.Length);
			Array.Clear(m_newW, 0, m_newW.Length);
			Array.Clear(m_curW, 0, m_curW.Length);
			Array.Clear(m_preW, 0, m_preW.Length);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="i">i=[2,N]</param>
		/// <returns></returns>
		double GetNewWAt(int i, double[] curW, double[] preW)
		{
			return lambda * (
				curW[i + 2] - 4.0 * curW[i + 1] + 6.0 * curW[i] - 4.0 * curW[i - 1] + curW[i - 2]
			) + 2.0 * curW[i] - preW[i];
		}

		void SetLeftBound(double[] newW, double[] curW)
		{
			newW[0] = m_iniW[0];
			newW[1] = m_iniW[1];
			newW[2] = m_iniW[2];
		}

		void SetRightBound(double[] newW, double[] curW)
		{
			newW[TotN - 1] = m_iniW[TotN - 1];
			newW[TotN - 2] = m_iniW[TotN - 2];
			newW[TotN - 3] = m_iniW[TotN - 3];
		}

		void SetInitialConditions()
		{
			m_iniW[0] = -1.0;
			m_iniW[1] = -0.5;
			m_iniW[2] = 0.0;
			for (int i = 3; i < TotN - 3; i++)
				m_iniW[i] = 0.01;
			m_iniW[TotN - 1] = -1.0;
			m_iniW[TotN - 2] = -0.5;
			m_iniW[TotN - 3] = 0.0;

			Array.Copy(m_iniW, m_preW, m_preW.Length);
			Array.Copy(m_iniW, m_curW, m_curW.Length);
		}

		public void Start()
		{
			SetInitialConditions();

			var preW = m_preW;
			var curW = m_curW;
			var newW = m_newW;

			for (int i = 0; i < LoopNum; i++)
			{
				SetLeftBound(newW, curW);
				SetRightBound(newW, curW);
				for (int j = 3; j < TotN - 3; j++)
				{
					newW[j] = GetNewWAt(j, curW, preW);
				}

				PrintArray(newW);

				var temp = preW;
				preW = curW;
				curW = newW;
				newW = temp;
				Array.Clear(newW, 0, newW.Length);

				m_lock.AcquireWriterLock(Timeout.Infinite);
				Array.Copy(m_curW, m_getW, m_getW.Length);
				m_lock.ReleaseWriterLock();
			}
		}

		public double[] GetW()
		{
			double[] ret = new double[TotN];
			m_lock.AcquireReaderLock(Timeout.Infinite);
			Array.Copy(m_curW, ret, ret.Length);
			m_lock.ReleaseReaderLock();

			return ret;
		}

		void PrintArray(double[] arr)
		{
			for(int i = 0; i < arr.Length - 1; i++)
				Trace.Write(arr[i].ToString() + ", ");
			Trace.WriteLine(arr[arr.Length - 1].ToString());
		}
	}
}
