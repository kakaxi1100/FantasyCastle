using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace board
{
    class Program
    {
        public enum Gender
        {
            男,
            女
        }
        public struct Player
        {
            //玩家姓名
            public string name;
            //玩家性别
            public Gender sex;
            //是否电脑
            public bool isHuman;
        }

        private static int mapNo = -1;
        private static int playerNums = -1;
        private static int humanNums = -1;
        private static int computerNums = -1;
        private static Player[] players = new Player[4];
        private static int[] map = new int[100];

        static void Main(string[] args)
        {
            #region 游戏开始选择界面
            GameHeader();
            #region 选择地图 1、显示地图缩略图
            Console.WriteLine("请选择游戏地图:");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("1:");
            SmallMap1();
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("2:");
            SmallMap2();
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("---------------------");
            #endregion
            #region 选择地图 2、选择
            while(true)
            {
                try
                {
                    mapNo = Convert.ToInt32(Console.ReadLine());
                    if (mapNo > 0 && mapNo < 3)
                    {
                        break;
                    }
                    else
                    {
                        Console.WriteLine("请输入正确地图编号！");
                    }
                }
                catch
                {
                    Console.WriteLine("请输入数字！");
                }
            }
            #endregion
            Console.Clear();
            GameHeader();
            #region 选择游戏人数和玩家个数
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("请选择游戏人数:1,2,3,4");
            while (true)
            {
                try
                {
                    playerNums = Convert.ToInt32(Console.ReadLine());
                    if (playerNums > 0 && playerNums < 5)
                    {
                        break;
                    }
                    else
                    {
                        Console.WriteLine("请输入正确的游戏人数！");
                    }
                }
                catch
                {
                    Console.WriteLine("请输入数字！");
                }
            }

            Console.WriteLine("请选择玩家人数:1,2,3,4");
            while (true)
            {
                try
                {
                    humanNums = Convert.ToInt32(Console.ReadLine());
                    if (humanNums > 0 && humanNums < 5 && humanNums <= playerNums)
                    {
                        computerNums = playerNums - humanNums;
                        break;
                    }
                    else
                    {
                        Console.WriteLine("请输入正确的玩家人数！");
                    }
                }
                catch
                {
                    Console.WriteLine("请输入数字！");
                }
            }

            string playerName;
            for (int i = 0; i < playerNums; i++)
			{
                Player p1;
                if (i < humanNums)
                {
                    Console.Write("请输入玩家{0}姓名:", i + 1);
                    playerName = Console.ReadLine();
                    p1.isHuman = true;
                    p1.sex = Gender.女;
                }
                else
                {
                    playerName = "电脑" + (i - humanNums + 1);
                    p1.isHuman = false;
                    p1.sex = Gender.男;
                }
                p1.name = playerName;
                players[i] = p1;
            }
            #endregion
            #endregion
            Console.Clear();
            #region 游戏进入主循环
            //1、画信息
            DrawInfo();
            //2、画地图
            DrawMap();
            #endregion
            Console.ReadKey();
        }

        private static void DrawMap()
        {
            //产生map
            MapCreator();
            switch (mapNo)
            {
                case 1:
                    RealMap1();
                    break;
                case 2:
                    RealMap2();
                    break;
                default:
                    break;
            }
        }

        private static void DrawInfo()
        {
            Console.ForegroundColor = ConsoleColor.Green;
            for (int i = 0; i < players.Length; i++)
            {
                if (players[i].name != null)
                {
                    Console.Write("玩家{0}:{1}  ", i + 1, players[i].name);
                }
            }
            Console.WriteLine();
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("□-普通, ×-暂停, →-前进, ←-后退, ※-随机事件, ◎-选择事件, ●-起点, ★-终点");
            Console.WriteLine();
        }

        /// <summary>
        /// 游戏头
        /// </summary>
        private static void GameHeader()
        {
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine("+-------------------------+");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("|    冒险棋游戏_v1.0      |");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("|                         |");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("|    作者：Ares           |");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("+-------------------------+");
        }

        private static void SmallMap1()
        {
            Console.ForegroundColor = ConsoleColor.DarkYellow;
            Console.WriteLine("□□□□");
            Console.WriteLine("      □");
            Console.WriteLine("□□□□");
            Console.WriteLine("□");
            Console.WriteLine("□□□□");
        }

        private static void SmallMap2()
        {
            Console.ForegroundColor = ConsoleColor.DarkYellow;
            Console.WriteLine("□□□□□");
            Console.WriteLine("□      □");
            Console.WriteLine("□      □");
            Console.WriteLine("□□□□□");
        }

        private static void MapCreator()
        {
            map[0] = 1;//起点是1
            map[map.Length - 1] = 2;//终点是2 
            Random r = new Random();
            int i;
            int j;
            for (i = 1; i < 99; i += 8)
            {
                j = i + 8;
                if(j > 98)
                {
                    j = 98;
                }
                j = r.Next(i, j);
                map[j] = 3;//后退是3
            }

            for (i = 1; i < 99; i += 10)
            {
                j = i + 8;
                if (j > 98)
                {
                    j = 98;
                }
                j = r.Next(i, j);
                map[j] = 4;//前进是4
            }

            for (i = 1; i < 99; i += 9)
            {
                j = i + 8;
                if (j > 98)
                {
                    j = 98;
                }
                j = r.Next(i, j);
                map[j] = 5;//暂停是5
            }

            for (i = 1; i < 99; i += 6)
            {
                j = i + 8;
                if (j > 98)
                {
                    j = 98;
                }
                j = r.Next(i, j);
                map[j] = 6;//随机事件是6
            }

            for (i = 1; i < 99; i += 6)
            {
                j = i + 8;
                if (j > 98)
                {
                    j = 98;
                }
                j = r.Next(i, j);
                map[j] = 8;//选择事件是7
            }
        }

        private static void RealMap1()
        {
            for (int i = 0; i < 30; i++)
            {
                Console.Write(MapPic(map[i]));
            }
            Console.WriteLine();

            for (int i = 30; i < 35; i++)
            {
                for (int j = 0; j < 29; j++)
                {
                    Console.Write("  ");
                }
                Console.WriteLine(MapPic(map[i]));       
            }

            for (int i = 64; i > 34; i--)
            {
                Console.Write(MapPic(map[i]));
            }
            Console.WriteLine();

            for (int i = 65; i < 70; i++)
            {
                Console.WriteLine(MapPic(map[i]));
            }

            for (int i = 70; i < 100; i++)
            {
                Console.Write(MapPic(map[i]));
            }
            Console.WriteLine();
        }

        private static void RealMap2()
        {
            for (int i = 0; i < 24; i++)
            {
                Console.Write(MapPic(map[i]));
            }

            for (int i = 99, j = 25; i > 74 && j < 50; i--, j++)
            {
                Console.Write(MapPic(map[i]));
                for (int k = 0; k < 24; k++)
                {
                    Console.Write("  ");
                }
                Console.WriteLine(MapPic(map[j]));
            }

            for (int i = 74; i > 49 ; i--)
            {
                Console.Write(MapPic(map[i]));
            }
            Console.WriteLine();
        }

        private static string MapPic(int type)
        {
            string str;
            switch (type)
            {
                case 0:
                    str = "□";
                    break;
                case 1:
                    str = "●";
                    break;
                case 2:
                    str = "★";
                    break;
                case 3:
                    str = "←";
                    break;
                case 4:
                    str = "→";
                    break;
                case 5:
                    str = "×";
                    break;
                case 6:
                    str = "※";
                    break;
                case 7:
                    str = "◎";
                    break;
                default:
                    str = "□";
                    break;
            }
            return str;
        }
    }
}
