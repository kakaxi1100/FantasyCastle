using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
            //玩家在地图上的位置
            public int pos;
            //玩家暂停的回合数
            public int stopNum;
        }

        private static int mapNo = -1;//地图编号
        private static int playerNums = -1;//游戏人数
        private static int humanNums = -1;//玩家人数
        private static int computerNums = -1;//电脑人数
        private static Player[] players = new Player[4];//玩家信息数组
        private static int[] map = new int[100];//地图数组
        private static int[] originMap = new int[100];//源数组
        private static int[] tilePlayers = new int[100];//每个tile上的player数量
        private static int curPlayer = 0;//当前玩家
        private static string keepTurnInfo = "";
        private static int turnState = 0;
        private static bool overFlag = false;
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
            Console.WriteLine("请选择游戏人数:2,3,4");
            while (true)
            {
                try
                {
                    playerNums = Convert.ToInt32(Console.ReadLine());
                    if (playerNums > 1 && playerNums < 5)
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
                p1.pos = 0;
                p1.stopNum = 0;
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
            //产生地图
            MapCreator();
            #region 游戏进入主循环
            while (!overFlag)
            {  
                //清屏
                Console.Clear();
                //1、画信息
                DrawInfo();
                //2、画地图
                DrawMap();
                //3、走步信息
                DrawTurn();

                Thread.Sleep(100);
            }
            #endregion
        }

        private static int walkStep = 0;
        private static void DrawTurn()
        {
            Console.ForegroundColor = ConsoleColor.Magenta;
            if (turnState == 0)//第一个状态掷骰子
            {
                if (players[curPlayer].stopNum > 0)
                {
                    Console.WriteLine("{0} 处于暂停状态", players[curPlayer].name);
                    turnState = 3;
                    return;
                }
                walkStep = 0;
                Random r = new Random();
                if (false && players[curPlayer].isHuman == true)
                {
                    Console.WriteLine("{0} 按任意键开始掷骰子", players[curPlayer].name);
                    Console.ReadKey(true);
                }
                else
                {
                    Console.WriteLine("{0} 开始掷骰子", players[curPlayer].name);
                }
                walkStep = r.Next(1, 7);
                Console.WriteLine("掷出点出: {0}", walkStep);
                turnState = 1;
            }
            else if(turnState == 1)//第二个状态玩家开始走步
            {
                PlayerRun(ref walkStep);
            }
            else if (turnState == 2)//第三个状态检查是否触发事件
            {
                CheckEvent();
            }
            else if(turnState == 3)//回合停止状态
            {
                if (players[curPlayer].stopNum == 0)
                {
                    turnState = 0;
                    return;
                }
                players[curPlayer].stopNum--;
                keepTurnInfo = players[curPlayer].name + " 还需暂停 " + players[curPlayer].stopNum + " 回合\n";
                turnState = 4;
            }
            else if (turnState == 4)//回合结束
            {
                keepTurnInfo = "";
                Console.WriteLine("{0} 回合结束", players[curPlayer].name);
                //更新当前玩家
                curPlayer++;
                if (curPlayer > playerNums - 1)
                {
                    curPlayer = 0;
                }

                turnState = 0;
            }
            else if (turnState == 5)//游戏结束状态
            {
                Console.WriteLine("■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□");
                Console.WriteLine("{0} 胜利！！", players[curPlayer].name);
                Console.WriteLine("■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□");
                overFlag = true;
                Console.ReadKey(true);
            }
            Console.Write(keepTurnInfo);
        }

        private static void CheckEvent()
        {
            int tileType = originMap[players[curPlayer].pos];
            switch (tileType)
            {
                case 2:
                    EndGameEvent();
                    break;
                case 3:
                    //后退
                    TurnBackEvent();
                    break;
                case 4:
                    //前进
                    GoAheadEvent();
                    break;
                case 5:
                    //暂停
                    StopTurnEvent();
                    break;
                default:
                    turnState = 4;
                    break;
            }
        }

        private static void StopTurnEvent()
        {
            Random r = new Random();
            int stopNum = r.Next(1, 4);
            players[curPlayer].stopNum = stopNum;
            keepTurnInfo = "玩家 " + players[curPlayer].name + " 触发暂停事件，暂停 " + stopNum + " 回合\n";
            turnState = 4;
        }

        private static void GoAheadEvent()
        {
            Random r = new Random();
            walkStep = r.Next(1, 7);
            keepTurnInfo = "玩家 " + players[curPlayer].name + " 触发前进事件，前进 " + walkStep + " 格\n";
            turnState = 1;
        }

        private static void TurnBackEvent()
        {
            Random r = new Random();
            walkStep = r.Next(-6, 0);
            keepTurnInfo = "玩家 " + players[curPlayer].name + " 触发后退事件，退后 " + (walkStep*-1) + " 格\n";
            turnState = 1;
        }

        private static void EndGameEvent()
        {
            turnState = 5;  
        }

        private static void PlayerRun(ref int num)
        {
            if (num == 0)
            {
                keepTurnInfo = "玩家 " + players[curPlayer].name + " 走步结束\n";
                turnState = 2;
                return;
            }
            if (players[curPlayer].pos >= 0 && players[curPlayer].pos <= 99)
            {
                if (num > 0)
                {          
                    players[curPlayer].pos++;
                    if (players[curPlayer].pos > 99)
                    {
                        players[curPlayer].pos = 98;
                        num = num * -1;
                    }
                    keepTurnInfo = "玩家 " + players[curPlayer].name + " 还要前进 " + num + " 步\n";
                    num--;
                }
                else
                {
                    players[curPlayer].pos--;
                    if (players[curPlayer].pos < 0)
                    {
                        players[curPlayer].pos = 0;
                        turnState = 2;
                        return;
                    }
                    keepTurnInfo = "玩家 " + players[curPlayer].name + " 还要后退 " + (num*-1) + " 步\n";
                    num++;
                }
            }
        }

        private static void CheckPlayerPos()
        {
            //1、检测玩家位置
            for (int i = 0; i < playerNums; i++)
            {
                map[players[i].pos] = i + 8;
            }
            //2、检查重叠区域
            CheckOverLap();
            for (int i = 0; i < tilePlayers.Length; i++)
            {
                if(tilePlayers[i] > 1)
                {
                    map[i] = tilePlayers[i] + 10;
                }
            }
        }

        private static void CheckOverLap()
        {
            //先将tilePlayers都置为0
            for (int i = 0; i < tilePlayers.Length; i++)
			{
			    tilePlayers[i] = 0;
			}
            for (int i = 0; i < playerNums; i++)
            {
                tilePlayers[players[i].pos] += 1;
            }
        }

        private static void DrawMap()
        {
            //还原成源数组
            changeMapToOrigin();
            //检查玩家位置
            CheckPlayerPos();
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
            Console.WriteLine();
        }
        //还原成源数组
        private static void changeMapToOrigin()
        {
            for (int i = 0; i < map.Length; i++)
            {
                map[i] = originMap[i];
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
            Console.WriteLine("□-普通, ×-暂停, →-前进, ←-后退, ●-起点, ★-终点");
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
            originMap[0] = 1;
            originMap[originMap.Length - 1] = 2;

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
                originMap[j] = 3;
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
                originMap[j] = 4;
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
                originMap[j] = 5;
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
                case 8:
                    str = "Ａ";//玩家1
                    break;
                case 9:
                    str = "Ｂ";//玩家2
                    break;
                case 10:
                    str = "Ｃ";//玩家3
                    break;
                case  11:
                    str = "Ｄ";//玩家4
                    break;
                case 12:
                    str = "②";//两个玩家重叠
                    break;
                case 13:
                    str = "③";//三个玩家重叠
                    break;
                case 14:
                    str = "④";//四个玩家重叠
                    break;
                default:
                    str = "□";
                    break;
            }
            return str;
        }
    }
}
