using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LoLWrapper
{
    public class SimpleLoL
    {

		public enum Status
		{
			AP = 0,
			ArmorPen,
			Armor,
			BaseAD,
			TotalAD
		}

		[DllImport("LoLInject.dll")]
		public static extern float GetPlayerStat(int stat);

		[DllImport("LoLInject.dll")]
		public static extern bool IsDead();

	}
}
