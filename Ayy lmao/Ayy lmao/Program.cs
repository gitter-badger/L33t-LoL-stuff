using LoLWrapper;

namespace Ayy_lmao
{
    static class Program
	{
		static void Main(string[] args)
		{
			SimpleLoL.IsDead();
			SimpleLoL.GetPlayerStat((int)SimpleLoL.Status.AP);
		}
	}
}
