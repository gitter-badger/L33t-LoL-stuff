using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LoLWrapper;

namespace Ayy_lmao
{
	class Program
	{
		static void Main(string[] args)
		{
			SimpleLoL.IsDead();
			SimpleLoL.GetPlayerStat((int)SimpleLoL.Status.AP);
		}
	}
}
