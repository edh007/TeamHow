using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

struct dataForMap
{
    public int x { get; set; }
    public int y { get; set; }
    public Catalogue type { get; set; }
    public Memo.Object obj { get; set; }
}

enum Catalogue { TURRET, FOG, BLANK, WALL, DOOR, TARGET, ALARM, Node, ENEMY, LASER }

namespace Memo
{
    public interface IMyInterface
    {
        void SetData(List<int> Data);
        void SetEnemy(List<int> e_Data, List<List<int?>> p_Data);
        void SetRotation(List<int> r_Data);
    }

    public partial class Form1 : Form, IMyInterface
    {
        String path = @"D:\";
        Map map = new Map();
        
        Point p = new Point(0, 0);
        Point Index = new Point();
        Point NodeP = new Point();
        Point Enemy_Point = new Point();
        Point Laser_Point = new Point();
        bool mousePositionCheckX = false;
        bool mousePositionCheckY = false;

        static bool checkNodeEnd = false;
        static bool checkEnemyEnd = false;
        static bool checkLaserEnd = false;
        List<int> listInt = new List<int>();
        List<int> enemyData = new List<int>();
        List<List<int?>> patrolData = new List<List<int?>>();
        List<int> rotation = new List<int>();

        Catalogue selectType = Catalogue.TURRET;
        Image _image = Properties.Resources.Turret;
        JObject m_obj;
        private Graphics GFX;
        Rectangle rec = new Rectangle(1070, 0, 32, 32);
        Pen pen = new Pen(Color.Aqua);
        List<dataForMap> datalist = new List<dataForMap>();
        //List<PictureBox> dataPictureBox;
        dataForMap data = new dataForMap();
        //int m_objectSelected = 0;

        Point mouse = new Point(0,0);
        bool checkWall = false;

        dataForMap wallDataF = new dataForMap();
        dataForMap wallDataS = new dataForMap();

        dataForMap wallDataLoadF = new dataForMap();
        dataForMap wallDataLoadS = new dataForMap();
        public Form1()
        {
            InitializeComponent();
            GFX = panel_map.CreateGraphics();
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.DoubleBuffer, true);
            this.DoubleBuffered = true;

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //ClientSize = new System.Drawing.Size(1530, 860);
            //ClientSize = new System.Drawing.Size(1563, 908);
            ClientSize = new System.Drawing.Size(1473, 879);
            this.panel_map.Size = new System.Drawing.Size(1024, 768);
            this.panel_display.Size = new System.Drawing.Size(1034, 778);
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            if(e.X <= panel_map.Location.X)
                mousePositionCheckX = true;
            if (e.Y <= panel_map.Location.Y)
                mousePositionCheckY = true;

            panel_map_MouseMove(sender, e);
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.X <= panel_map.Location.X)
                mousePositionCheckX = true;
            if (e.Y <= panel_map.Location.Y)
                mousePositionCheckY = true;
            panel_map_MouseClick(sender, e);
        }

        public void SetData(List<int> Data)
        {
            listInt = Data;
            checkNodeEnd = true;
        }

        public void SetRotation(List<int> r_Data)
        {
            rotation = r_Data;
            checkLaserEnd = true;
        }

        public void SetEnemy(List<int> e_Data, List<List<int?>> p_Data)
        {
            //0 - Speed
            //1 - Type
            //    Type : 0 - Normal, 1 - Web, 2 - Bullet, 3 - Defender, 4 - Bomber, 5 - Anti
            //2 - Patrol Type
            //    Type : 0 - Shuttle, 1 - Linear
            enemyData = e_Data;
            patrolData = p_Data;
            checkEnemyEnd = true;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            //GFX = this.CreateGraphics();
            //GFX = e.Graphics;
            //Graphics g = e.Graphics;
            //this.DoubleBuffered = true;
            if (m_obj != null)
                SettingDataList();

            rec.Location = mouse;
            GFX.DrawRectangle(pen, rec);

            //panel_map.Refresh();
            //GFX.DrawRectangle(pen, rec);
        }


        private JObject NodeMaker(dataForMap dt)
        {
            try
            {
                LogicValues m_values = new LogicValues();

                List<List<int>> list = new List<List<int>>();
                List<int> i = new List<int>();
                List<int> n = new List<int>();
                i.Add(listInt[0]);
                i.Add(listInt[1]);
                n.Add(Index.X);
                n.Add(Index.Y);
                list.Add(i);
                list.Add(n);
                m_values.Node = new List<List<List<int>>>();
                m_values.Node.Add(list);

                for (int index = 0; index < map.Object.Length; index++)
                {
                    //dataForMap tmp = new dataForMap();
                    data.obj = map.Object[index];
                    if (map.Object[index].Component == null && map.Object[index].ArcheType.ToString() == "NONE")
                    {
                        for (int k = 0; k < map.Object[index].Logic.Count; k++)
                        {
                            if (map.Object[index].Logic[k].Key.ToString() == "NODESETTOR")
                            {
                                map.Object[index].Logic[k].LogicValues.Node.Add(list);
                                textBox1.Text = Newtonsoft.Json.JsonConvert.SerializeObject(map);
                                _image = Properties.Resources.Node;
                                GFX.DrawImage(_image, new Point(dt.x + 512, (dt.y) * -1 + 384));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.GetType().Name + ": " + ex.Message, "Error");
            }
            return null;
        }

        #region Panel_Map
        private void panel_map_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                p.X = e.X - 512;
                p.Y = (e.Y) * -1 + 384;

                if (mousePositionCheckX == true)
                    p.X = ((panel_map.Size.Width / 2) + panel_map.Location.X - e.X) * (-1);
                if (mousePositionCheckY == true)
                    p.Y = ((panel_map.Size.Height / 2) + panel_map.Location.Y - e.Y);

                int lastx = p.X % 32;
                int lasty = p.Y % 32;

                if (p.X % 32 != 0 || p.Y % 32 != 0)
                {
                    lastx = p.X % 32;
                    lasty = p.Y % 32;

                    //if (lastx < 0)
                        p.X -= lastx;
                    //else
                    //    p.X -= lastx;
                    //if (lasty > 0)
                        p.Y -= lasty;
                    //else
                    //    p.Y -= lasty;
                }

                data.type = selectType;
                data.x = p.X;
                data.y = p.Y;

                datalist.Add(data);

                if (m_obj != null)
                {
                    if(selectType == Catalogue.Node)
                    {
                        Form2 tmpForm = new Form2(this as IMyInterface);
                        tmpForm.ChangeTitle("Node");
                        tmpForm.Show();
                        Index.X = data.x;
                        Index.Y = data.y;

                    }
                    else if(selectType == Catalogue.ENEMY)
                    {
                        Form2 tmpForm = new Form2(this as IMyInterface);
                        tmpForm.ChangeTitle("Enemy Setting");
                        tmpForm.Show();
                        Enemy_Point.X = data.x;
                        Enemy_Point.Y = data.y;

                    }
                    else if (selectType == Catalogue.LASER)
                    {
                        Form2 tmpForm = new Form2(this as IMyInterface);
                        tmpForm.ChangeTitle("Laser Setting");
                        tmpForm.Show();
                        Laser_Point.X = data.x;
                        Laser_Point.Y = data.y;
                    }
                    else if (selectType != Catalogue.BLANK && selectType != Catalogue.WALL)
                    {
                        foreach (var token in m_obj)
                        {
                            if (token.Key.ToString() == "Object")
                            {
                                JArray o = (JArray)token.Value;
                                ArcheTypeMaker(data);
                                //o.Add(ArcheTypeMaker(data));
                            }
                        }
                        textBox1.Text = Newtonsoft.Json.JsonConvert.SerializeObject(map);
                        GFX.DrawImage(_image, new Point(data.x + 512, (data.y * -1) + 384));
                        
                        //textBox1.Text = m_obj.ToString();
                    }
                    else if(selectType == Catalogue.BLANK)
                    {
                        int tmp = -1;
                        for (int i = 0; i < map.Object.Length; i++)
                        {
                            if (map.Object[i] != null)
                            {
                                if (map.Object[i].ArcheType.ToString() == "NONE")
                                {
                                    if (map.Object[i].Logic != null)
                                    {
                                        for (int j = 0; j < map.Object[i].Logic.Count; j++)
                                        {
                                            if (map.Object[i].Logic[j].Key.ToString() == "NODESETTOR")
                                            {
                                                for (int k = 0; k < map.Object[i].Logic[j].LogicValues.Node.Count; k++)
                                                {
                                                    int trgtX = map.Object[i].Logic[j].LogicValues.Node[k][1][0];
                                                    int trgtY = map.Object[i].Logic[j].LogicValues.Node[k][1][1];

                                                    if (data.x == trgtX && data.y == trgtY)
                                                    {
                                                        map.Object[i].Logic[j].LogicValues.Node.RemoveAt(k);
                                                    }

                                                }
                                            }
                                        }
                                    }

                                }
                                else if (map.Object[i].ArcheType.ToString() == "WALL")
                                {
                                    if(data.x == map.Object[i].Component[0].Values.Position[0])
                                    {
                                        int t = map.Object[i].Component[0].Values.Position[1];

                                        int count = (map.Object[i].Component[0].Values.Scale[1]) / 32;
                                        if(count % 2 == 0)
                                        {
                                            if ((data.y - ((count - 1) * 16) < t) && (data.y + ((count - 1) * 16) > t))
                                            {
                                                tmp = i;
                                                map.Object[i] = null;
                                            }
                                        }
                                        else
                                        {
                                            if ((data.y - ((count-1) * 16) < t) && (data.y + ((count - 1) * 16) > t))
                                            {
                                                tmp = i;
                                                map.Object[i] = null;
                                            }
                                        }

                                    }
                                    else if (data.y == map.Object[i].Component[0].Values.Position[1])
                                    {
                                        int t = map.Object[i].Component[0].Values.Position[0];

                                        int count = (map.Object[i].Component[0].Values.Scale[0]) / 32;
                                        if (count % 2 == 0)
                                        {
                                            if ((data.x - ((count - 1) * 16) < t) && (data.x + ((count - 1) * 16) > t))
                                            {
                                                tmp = i;
                                                map.Object[i] = null;
                                            }
                                        }
                                        else
                                        {
                                            if ((data.x - ((count - 1) * 16) < t) && (data.x + ((count - 1) * 16) > t))
                                            {
                                                tmp = i;
                                                map.Object[i] = null;
                                            }
                                        }
                                    }
                                }
                                else if (map.Object[i].Component != null)
                                    if(((data.x == map.Object[i].Component[0].Values.Position[0] 
                                    && data.y == map.Object[i].Component[0].Values.Position[1])))
                                {
                                    tmp = i;
                                    map.Object[i] = null;
                                }

                                if (tmp != -1 && ((i + 1) < map.Object.Length))
                                    map.Object[i] = map.Object[i + 1];
                                else if (tmp != -1 && (i + 1) == map.Object.Length)
                                {
                                    map.Object[i] = null;
                                    map.Object = setLength(map.Object, map.Object.Length - 1);
                                }
                            }

                        }
                        textBox1.Text = Newtonsoft.Json.JsonConvert.SerializeObject(map);
                        //GFX.DrawImage(_image, new Point(data.x + 512, (data.y * -1) + 384));
                    }
                    else
                    {
                        if (checkWall == false)
                        {
                            wallDataF = data;
                            checkWall = true;
                        }
                        else if (checkWall == true)
                        {
                            wallDataS = data;
                            if ((wallDataF.x == wallDataS.x) && (wallDataF.y != wallDataS.y))
                            {

                            }
                            else if((wallDataF.x != wallDataS.x) && (wallDataF.y == wallDataS.y))
                            {

                            }

                            if ((wallDataF.x == wallDataS.x) && (wallDataF.y != wallDataS.y)
                            || (wallDataF.x != wallDataS.x) && (wallDataF.y == wallDataS.y))
                            {
                                foreach (var token in m_obj)
                                {
                                    if (token.Key.ToString() == "Object")
                                    {
                                        JArray o = (JArray)token.Value;
                                        WallMaker(data);
                                        //o.Add(ArcheTypeMaker(data));
                                    }
                                }

                                textBox1.Text = Newtonsoft.Json.JsonConvert.SerializeObject(map);

                                DrawingWall(wallDataF, wallDataS);
                            }
                            checkWall = false;
                        }
                    }
                }
            }
            if (m_obj != null)
                SettingDataList();

        }

        #region Wall
        private void DrawingWall(dataForMap dtF, dataForMap dtS)
        {
            int smallerValue = 0;
            if (dtF.x == dtS.x)
            {
                int count = (dtF.y - dtS.y) / 32;
                smallerValue = dtF.y;
                if (count < 0)
                {
                    smallerValue = dtS.y;
                    count *= -1;
                }
                for (int i = 0; i < count; i++)
                {
                    GFX.DrawImage(_image, new Point(data.x + 512, (smallerValue * -1) + 384 + (i * 32)));
                }
            }
            else if (dtF.x != dtS.x)
            {
                int count = (dtF.x - dtS.x) / 32;
                smallerValue = dtS.x;
                if (count < 0)
                {
                    smallerValue = dtF.x;
                    count *= -1;
                }
                for (int i = 0; i < count; i++)
                {
                    
                    GFX.DrawImage(_image, new Point((smallerValue) + 512 + (i * 32), (data.y * -1) + 384));
                }
            }
        }

        private JObject WallMaker(dataForMap dt)
        {
            try
            {
                dt.x = (wallDataF.x + wallDataS.x) / 2;
                dt.y = (wallDataF.y + wallDataS.y) / 2;

                Component m_component = new Component();
                Values m_values = new Values();

                m_values.Position = setLength(m_values.Position, 3);
                m_values.Position[0] = dt.x;
                m_values.Position[1] = dt.y;
                m_values.Position[2] = 0;

                m_values.Scale = setLength(m_values.Scale, 3);
                if (dt.x == wallDataF.x)
                {
                    // Setting the thickness of the wall
                    m_values.Scale[0] = 32;
                    if (wallDataF.y > wallDataS.y)
                        m_values.Scale[1] = (wallDataF.y - wallDataS.y);
                    else
                    {
                        m_values.Scale[1] = (wallDataS.y - wallDataF.y);
                        m_values.Position[1] -= 32;
                    }
                }
                else if (dt.y == wallDataF.y)
                {
                    if (wallDataF.x > wallDataS.x)
                    {
                        m_values.Scale[0] = (wallDataF.x - wallDataS.x);
                        m_values.Position[0] += 32;
                    }
                    else
                        m_values.Scale[0] = (wallDataS.x - wallDataF.x);
                    m_values.Scale[1] = 32;
                }
                m_values.Scale[2] = 0;

                m_component.Key = "TRANSFORM";
                m_component.Values = m_values;

                Object m_object = new Object();

                m_object.Component = setLength(m_object.Component, 1);
                m_object.Component[0] = m_component;
                m_object.ArcheType = selectType.ToString();

                map.Object = setLength(map.Object, map.Object.Length + 1);
                map.Object[map.Object.Length - 1] = m_object;

                string at = selectType.ToString();
                string str = "{ \"ArcheType\" : \"" + at + "\", \"Component\": [ { \"key\": \"TRANSFORM\", \"values\": { \"Position\": [ " + dt.x + ", " + dt.y + ", -5 ] }} ] }";
                JObject tmp = JObject.Parse(str);
                return tmp;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.GetType().Name + ": " + ex.Message, "Error");
            }
            return null;
        }
        #endregion

        private JObject LaserMaker(dataForMap dt)
        {
            try
            {
                //rotation[0];
                Component m_component = new Component();
                Values m_values = new Values();
                m_values.Position = setLength(m_values.Position, 3);
                m_values.Position[0] = Laser_Point.X;
                m_values.Position[1] = Laser_Point.Y;
                m_values.Position[2] = 0;
                m_values.Scale = setLength(m_values.Scale, 3);
                m_values.Scale[0] = 240;
                m_values.Scale[1] = 50;
                m_values.Scale[2] = 0;
                m_values.Rotation = rotation[0];

                m_component.Key = "TRANSFORM";
                m_component.Values = m_values;

                Object m_object = new Object();

                m_object.Component = setLength(m_object.Component, 1);
                m_object.Component[0] = m_component;
                m_object.ArcheType = selectType.ToString();

                map.Object = setLength(map.Object, map.Object.Length + 1);
                map.Object[map.Object.Length - 1] = m_object;

                textBox1.Text = Newtonsoft.Json.JsonConvert.SerializeObject(map);
                //GFX.DrawImage(_image, new Point(Enemy_Point.X + 512, (Enemy_Point.Y * -1) + 384));
                GFX.DrawImage(_image, new Point(Enemy_Point.X, (Enemy_Point.Y)));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.GetType().Name + ": " + ex.Message, "Error");
            }
            return null;
        }

        private JObject EnemyMaker(dataForMap dt)
        {
            try
            {
                Component m_component = new Component();
                Values m_values = new Values();
                //Logic logic_patrol = new Logic();
                Logic logic_enemy = new Logic();

                m_values.Position = setLength(m_values.Position, 3);
                m_values.Position[0] = Enemy_Point.X;
                m_values.Position[1] = Enemy_Point.Y;
                m_values.Position[2] = 0;
                m_values.Scale = setLength(m_values.Scale, 3);
                m_values.Scale[0] = 125;
                m_values.Scale[1] = 100;
                m_values.Scale[2] = 0;

                //if(enemyData[5] != null)
                m_values.Rotation = enemyData[3];
                
                m_component.Key = "TRANSFORM";
                m_component.Values = m_values;

                Object m_object = new Object();

                m_object.Component = setLength(m_object.Component, 1);

                m_object.Component[0] = m_component;
                m_object.ArcheType = selectType.ToString();

                logic_enemy.Key = "ENEMY";
                //logic_patrol.Key = "PATROL";

                //0 - Speed
                //1 - FootStep
                //2 - Distance
                //3 - Type
                //    Type : 0 - Normal, 1 - Web, 2 - Bullet, 3 - Drugger, 4 - Bomber
                //4 - Patrol Type
                //    Type : 0 - Shuttle, 2 - Linear
                logic_enemy.LogicValues = new LogicValues();
                //logic_patrol.LogicValues = new LogicValues();

                logic_enemy.LogicValues.Speed = enemyData[0];
                //logic_enemy.LogicValues.Footstep = enemyData[1];
                //logic_enemy.LogicValues.Distance = enemyData[1];

                if (enemyData[1] == 0)
                    logic_enemy.LogicValues.EnemyType = "NORMAL";
                else if (enemyData[1] == 1)
                    logic_enemy.LogicValues.EnemyType = "WEB";
                else if (enemyData[1] == 2)
                    logic_enemy.LogicValues.EnemyType = "BULLET";
                else if (enemyData[1] == 3)
                    logic_enemy.LogicValues.EnemyType = "DEFENDER";
                else if (enemyData[1] == 4)
                    logic_enemy.LogicValues.EnemyType = "BOMBER";
                else if (enemyData[1] == 5)
                    logic_enemy.LogicValues.EnemyType = "ANTI";

                if (enemyData[2] == 0)
                    logic_enemy.LogicValues.PatrolType = "SHUTTLE";
                else if (enemyData[2] == 1)
                    logic_enemy.LogicValues.PatrolType = "LINEAR";

                logic_enemy.LogicValues.Point = patrolData;

                m_object.Logic = new List<Logic>();

                m_object.Logic.Add(logic_enemy);
                //m_object.Logic.Add(logic_patrol);

                map.Object = setLength(map.Object, map.Object.Length + 1);
                map.Object[map.Object.Length - 1] = m_object;

                textBox1.Text = Newtonsoft.Json.JsonConvert.SerializeObject(map);
                GFX.DrawImage(_image, new Point(Enemy_Point.X + 512, (Enemy_Point.Y * -1) + 384));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.GetType().Name + ": " + ex.Message, "Error");
            }
            return null;
        }

        private void panel_map_MouseMove(object sender, MouseEventArgs e)
        {
            if (checkNodeEnd == true)
            {
                NodeMaker(data);

                checkNodeEnd = false;
            }

            if (checkEnemyEnd == true)
            {
                EnemyMaker(data);

                checkEnemyEnd = false;
            }

            if (checkLaserEnd == true)
            {
                LaserMaker(data);

                checkLaserEnd = false;
            }

            if (m_obj != null)
                SettingDataList();
            
            int x, y;
            x = e.X - 512;
            y = (e.Y) * -1 + 384;

            if (mousePositionCheckX == true)
                x = ((panel_map.Size.Width / 2) + panel_map.Location.X - e.X) * (-1);
            if (mousePositionCheckY == true)
                y = ((panel_map.Size.Height / 2) + panel_map.Location.Y - e.Y);

            toolStripStatusLabel1.Text = "( In Game: " + x + ", " + y + " ), ( On Panel: " + e.X + ", " + e.Y + " )";

            int lastx = x % 32;
            int lasty = y % 32;

            if (x % 32 != 0 || y % 32 != 0)
            {
                lastx = x % 32;
                lasty = y % 32;

                x -= lastx;
                y -= lasty;
            }

            mouse.X = x + 512;
            mouse.Y = (y*-1) + 384;


            //if (m_obj != null)
            //    SettingDataList();

            //rec.Location = mouse;
            //GFX.DrawRectangle(pen, rec);
            mousePositionCheckX = false;
            mousePositionCheckY = false;
            panel_map.Refresh();

        }
        #endregion

        #region PictureList
        public void SettingDataList()
        {
            for (int index = 0; index < map.Object.Length; index++)
            {
                //dataForMap tmp = new dataForMap();
                data.obj = map.Object[index];

                if(map.Object[index].Component != null)
                {
                    for(int i = 0; i < map.Object[index].Component.Length; i++)
                    {
                        if (map.Object[index].Component[i].Key.ToString() == "TRANSFORM")
                        {
                            data.x = map.Object[index].Component[i].Values.Position[0];
                            data.y = map.Object[index].Component[i].Values.Position[1];
                            if(map.Object[index].ArcheType.ToString() == "WALL")
                            {
                                int x = map.Object[index].Component[i].Values.Scale[0];
                                int y = map.Object[index].Component[i].Values.Scale[1];
                                if(x>y)
                                {
                                    wallDataLoadF.y = data.y;
                                    wallDataLoadS.y = data.y;
                                    wallDataLoadF.x = data.x - (x / 2);
                                    wallDataLoadS.x = data.x + (x / 2);
                                }           
                                else        
                                {           
                                    wallDataLoadF.x = data.x;
                                    wallDataLoadS.x = data.x;
                                    wallDataLoadF.y = data.y - (y / 2);
                                    wallDataLoadS.y = data.y + (y / 2);
                                }
                            }
                        }
                    }
                }
                else if(map.Object[index].Component == null && map.Object[index].ArcheType.ToString() == "NONE")
                {
                    for (int i = 0; i < map.Object[index].Logic.Count; i++)
                    {
                        if(map.Object[index].Logic[i].Key.ToString() == "NODESETTOR")
                        {
                            for(int j = 0; j < map.Object[index].Logic[i].LogicValues.Node.Count; j++)
                            {
                                // Index
                                //Index.X = map.Object[index].Logic[i].LogicValues.Node[j][0][0];
                                //Index.Y = map.Object[index].Logic[i].LogicValues.Node[j][0][1];

                                NodeP.X = map.Object[index].Logic[i].LogicValues.Node[j][1][0];
                                NodeP.Y = map.Object[index].Logic[i].LogicValues.Node[j][1][1];

                                _image = Properties.Resources.Node;
                                GFX.DrawImage(_image, new Point(NodeP.X + 512, (NodeP.Y) * -1 + 384));
                            }
                        }
                        else if (map.Object[index].Logic[i].Key.ToString() == "FOOTSTEP" && index != (map.Object.Length - 1))
                        {
                            map.Object[index] = map.Object[index + 1];
                            map.Object[index + 1] = null;
                            map.Object = setLength(map.Object, map.Object.Length - 1);
                            textBox1.Text = Newtonsoft.Json.JsonConvert.SerializeObject(map);
                            break;
                        }
                    }
                }

                //datalist.Add();
                string type = map.Object[index].ArcheType.ToString();
                if (type == "TURRET")
                {
                    _image = Properties.Resources.Turret;
                    GFX.DrawImage(_image, new Point(data.x + 512, (data.y) * -1 + 384));
                }
                else if (type == "FOG")
                {
                    _image = Properties.Resources.Fog;
                    GFX.DrawImage(_image, new Point(data.x + 512, (data.y) * -1 + 384));
                }
                else if (type == "LASER")
                {
                    _image = Properties.Resources.Laser;
                    GFX.DrawImage(_image, new Point(data.x + 512, (data.y) * -1 + 384));
                }
                else if (type == "ALARM")
                {
                    _image = Properties.Resources.Radar;
                    GFX.DrawImage(_image, new Point(data.x + 512, (data.y) * -1 + 384));
                }
                else if (type == "DOOR")
                {
                    _image = Properties.Resources.Exit;
                    GFX.DrawImage(_image, new Point(data.x + 512, (data.y) * -1 + 384));
                }
                else if (type == "TARGET")
                {
                    _image = Properties.Resources.Target;
                    GFX.DrawImage(_image, new Point(data.x + 512, (data.y) * -1 + 384));
                }
                else if (type == "ENEMY")
                {
                    _image = Properties.Resources.Enemy;
                    for (int i = 0; i< map.Object[index].Logic.Count; i++)
                    {
                        if(map.Object[index].Logic[i].LogicValues.Type == null && map.Object[index].Logic[i].LogicValues.Type != null)
                            map.Object[index].Logic[i].LogicValues.Type = map.Object[index].Logic[i].LogicValues.Type;
                        if (map.Object[index].Logic[i].Key.ToString() == "ENEMY")
                        {
                            if(map.Object[index].Logic[i].LogicValues.EnemyType.ToString() == "NORMAL")
                                _image = Properties.Resources.Normal;
                            else if (map.Object[index].Logic[i].LogicValues.EnemyType.ToString() == "BULLET")
                                _image = Properties.Resources.Bullet;
                            else if (map.Object[index].Logic[i].LogicValues.EnemyType.ToString() == "WEB")
                                _image = Properties.Resources.Web;
                            else if (map.Object[index].Logic[i].LogicValues.EnemyType.ToString() == "DRUGGER")
                                _image = Properties.Resources.Drugger;
                            else if (map.Object[index].Logic[i].LogicValues.EnemyType.ToString() == "BOMBER")
                                _image = Properties.Resources.Bomber;
                            else if (map.Object[index].Logic[i].LogicValues.EnemyType.ToString() == "ANTI")
                                _image = Properties.Resources.Anti;
                            else if (map.Object[index].Logic[i].LogicValues.EnemyType.ToString() == "DEFENDER")
                                _image = Properties.Resources.Defender;
                        }
                    }
                    
                    
                    GFX.DrawImage(_image, new Point(data.x + 512, (data.y) * -1 + 384));
                }
                else if (type == "WALL")
                {
                    _image = Properties.Resources.Wall;
                    DrawingWall(wallDataLoadF, wallDataLoadS);
                }
                datalist.Add(data);
            }
        }

        private void pictureBox_Turret_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Turret;
            selectType = Catalogue.TURRET;
        }

        private void pictureBox_Fog_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Fog;
            selectType = Catalogue.FOG;
        }

        private void pictureBox_Rect_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Rect;
            selectType = Catalogue.BLANK;
        }

        private void pictureBox_Wall_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Wall;
            selectType = Catalogue.WALL;
        }

        private void pictureBox_Exit_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Exit;
            selectType = Catalogue.DOOR;
        }

        private void pictureBox_Target_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Target;
            selectType = Catalogue.TARGET;
        }

        private void pictureBox_Glass_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Radar;
            selectType = Catalogue.ALARM;
        }

        private void pictureBox_Node_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Node;
            selectType = Catalogue.Node;
        }

        private void pictureBox_Enemy_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Enemy;
            selectType = Catalogue.ENEMY;
        }

        private void pictureBox_Laser_MouseClick(object sender, MouseEventArgs e)
        {
            _image = Properties.Resources.Laser;
            selectType = Catalogue.LASER;
        }

        private void drawDataToPanel()
        {
        }

        #endregion

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            textBox1.ScrollBars = ScrollBars.Vertical;
        }

        private void menuToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }



        #region SaveLoadOpen
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //save
            if (File.Exists(path))
            {
                File.SetAttributes(path, FileAttributes.Normal);
                FileStream fs = new FileStream(path,
                FileMode.Truncate, FileAccess.Write);
                StreamWriter sw = new StreamWriter(fs);
                sw.WriteLine(textBox1.Text);
                sw.Flush();
                sw.Close();
                fs.Close();
            }
            else
            {
                //to save a first file
                SaveFileDialog pFileDlg = new SaveFileDialog();
                pFileDlg.Filter = "json Files(*.json)|*.json|All Files(*.*)|*.*";
                pFileDlg.Title = "다른 이름으로 저장";
                if (pFileDlg.ShowDialog() == DialogResult.OK)
                {
                    path = pFileDlg.FileName;
                    //name = pFileDlg.SafeFileName.Substring(0, pFileDlg.SafeFileName.Length - 4);
                    // ToDo
                    File.WriteAllText(path, textBox1.Text);
                    this.Text = path;
                }
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //save as
            //to save a first file
            SaveFileDialog pFileDlg = new SaveFileDialog();
            pFileDlg.Filter = "json Files(*.json)|*.json|All Files(*.*)|*.*";
            pFileDlg.Title = "다른 이름으로 저장";
            if (pFileDlg.ShowDialog() == DialogResult.OK)
            {
                path = pFileDlg.FileName;
                // ToDo
                File.WriteAllText(path, textBox1.Text);

                this.Text = path;
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }



        private JObject ArcheTypeMaker(dataForMap dt)
        {
            try
            {
                Component m_component = new Component();
                Values m_values = new Values();
                m_values.Position = setLength(m_values.Position, 3);
                m_values.Position[0] = dt.x;
                m_values.Position[1] = dt.y;
                m_values.Position[2] = 0;

                if (selectType.ToString() == "PLAYER")
                {
                    m_values.Scale = setLength(m_values.Scale, 3);
                    m_values.Scale[0] = 125;
                    m_values.Scale[1] = 100;
                    m_values.Scale[2] = 0;
                }
                else
                {
                    m_values.Scale = setLength(m_values.Scale, 3);
                    m_values.Scale[0] = 50;
                    m_values.Scale[1] = 50;
                    m_values.Scale[2] = 0;
                }
                m_component.Key = "TRANSFORM";
                m_component.Values = m_values;

                Object m_object = new Object();

                m_object.Component = setLength(m_object.Component, 1);
                m_object.Component[0] = m_component;
                m_object.ArcheType = selectType.ToString();

                map.Object = setLength(map.Object, map.Object.Length + 1);
                map.Object[map.Object.Length-1] = m_object;

                string at = selectType.ToString();
                string str = "{ \"ArcheType\" : \"" + at + "\", \"Component\": [ { \"key\": \"TRANSFORM\", \"values\": { \"Position\": [ " + dt.x + ", " + dt.y + ", -5 ] }} ] }";
                JObject tmp = JObject.Parse(str);
                return tmp;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.GetType().Name + ": " + ex.Message, "Error");
            }
            return null;
        }



        //
        private void openFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //open file
            OpenFileDialog pFileDlg = new OpenFileDialog();
            pFileDlg.Filter = "json Files(*.json)|*.json|All Files(*.*)|*.*";
            pFileDlg.Title = "[파일 불러오기]파일을 선택하여 주세요.";
            if (pFileDlg.ShowDialog() == DialogResult.OK)
            {
                //Clear the map
                GFX.Clear(Color.White);

                path = pFileDlg.FileName;
                // ToDo
                textBox1.Text = File.ReadAllText(path);
                try
                {
                    string json = textBox1.Text;

                    //Load Json Files
                    m_obj = JObject.Parse(json);

                    map = Newtonsoft.Json.JsonConvert.DeserializeObject<Map>(json);
                    //MessageBox.Show(map.ToString());
                    //SettingArcheTypeTex();
                    SettingDataList();

                    treeView1.Nodes.Clear();
                    TreeNode parent = Json2Tree(m_obj);
                    parent.Text = "Map Data";
                    treeView1.Nodes.Add(parent);
                    

                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.GetType().Name + ": " + ex.Message, "Error");
                }
                this.Text = path;
            }
        }
        #endregion

        #region JsonTree
        private TreeNode Json2Tree(JObject obj)
        {
            //create the parent node
            TreeNode parent = new TreeNode();
            //loop through the obj. all token should be pair<key, value>
            foreach (var token in obj)
            {
                //change the display Content of the parent
                parent.Text = token.Key.ToString();
                //create the child node
                TreeNode child = new TreeNode();
                child.Text = token.Key.ToString();
                //check if the value is of type obj recall the method
                if (token.Value.Type.ToString() == "Object")
                {
                    // child.Text = token.Key.ToString();
                    //create a new JObject using the the Token.value
                    JObject o = (JObject)token.Value;
                    
                    //recall the method
                    child = Json2Tree(o);

                    //Add from the stack
                    child.Text = token.Key.ToString();
                    
                    //add the child to the parentNode
                    parent.Nodes.Add(child);
                }
                //if type is of array
                else if (token.Value.Type.ToString() == "Array")
                {
                    int ix = -1;
                    //  child.Text = token.Key.ToString();
                    //loop though the array
                    foreach (var itm in token.Value)
                    {
                        //check if value is an Array of objects
                        if (itm.Type.ToString() == "Object")
                        {
                            TreeNode objTN = new TreeNode();
                            //child.Text = token.Key.ToString();
                            //call back the method
                            ix++;

                            JObject o = (JObject)itm;
                            objTN = Json2Tree(o);
                            objTN.Text = token.Key.ToString() + "[" + ix + "]";
                            child.Nodes.Add(objTN);
                            //parent.Nodes.Add(child);
                        }
                        //regular array string, int, etc
                        else if (itm.Type.ToString() == "Array")
                        {
                            ix++;
                            TreeNode dataArray = new TreeNode();
                            foreach (var data in itm)
                            {
                                dataArray.Text = token.Key.ToString() + "[" + ix + "]";
                                dataArray.Nodes.Add(data.ToString());
                            }
                            child.Nodes.Add(dataArray);
                        }

                        else
                        {
                            child.Nodes.Add(itm.ToString());
                        }
                    }
                    parent.Nodes.Add(child);
                }
                else
                {
                    //if token.Value is not nested
                    // child.Text = token.Key.ToString();
                    //change the value into N/A if value == null or an empty string 
                    if (token.Value.ToString() == "")
                        child.Nodes.Add("N/A");
                    else
                        child.Nodes.Add(token.Value.ToString());
                    parent.Nodes.Add(child);
                }
            }
            return parent;

        }
        #endregion

        #region JsonFunc
        static Object[] setLength(Object[] arr, int length)
        {
            Array.Resize(ref arr, length);
            return arr;
        }

        static int[] setLength(int[] arr, int length)
        {
            Array.Resize(ref arr, length);
            return arr;
        }

        static Component[] setLength(Component[] arr, int length)
        {
            Array.Resize(ref arr, length);
            return arr;
        }
        #endregion

        private void FootstepLogicCreator()
        {
            Object foot = new Object();
            foot.ArcheType = "NONE";
            Logic f = new Logic();
            f.Key = "FOOTSTEP";
            f.LogicValues = new LogicValues();
            foot.Logic = new List<Logic>();
            foot.Logic.Add(f);

            map.Object = setLength(map.Object, map.Object.Length + 1);
            map.Object[map.Object.Length - 1] = foot;
        }

        private void pressAfterMappingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Add FOOTSTEP LOGIC
            //if(map.Object[map.Object.Length - 1].ArcheType.ToString() != "NONE")
            //    FootstepLogicCreator();
            //else
            //{
            //    if (map.Object[map.Object.Length - 1].Logic.Count > 0)
            //    {
            //        if(map.Object[map.Object.Length - 1].Logic[0].Key.ToString() != "FOOTSTEP")
            //            FootstepLogicCreator();
            //    }
            //    else
            //        FootstepLogicCreator();
            //}

            //GFX.Clear(Color.White);
            var result = JsonConvert.SerializeObject(map,
            new JsonSerializerSettings()
            {
                NullValueHandling = NullValueHandling.Ignore
            });

            textBox1.Text = result;




        }


    }

    #region JsonMap
    internal class Map
    {
        [JsonProperty("Stage")]
        public Stage[] Stage { get; set; }

        [JsonProperty("Object")]
        public Object[] Object { get; set; }
    }

    internal class Stage
    {

        [JsonProperty("Background")]
        public int[] Background { get; set; }

        [JsonProperty("Camera")]
        public int[] Camera { get; set; }

        [JsonProperty("BGM")]
        public string BGM { get; set; }

        [JsonProperty("Audio")]
        public object[] Audio { get; set; }
    }

    internal class Object
    {

        [JsonProperty("ArcheType")]
        public string ArcheType { get; set; }

        [JsonProperty("Component")]
        public Component[] Component { get; set; }

        [JsonProperty("Logic")]
        public List<Logic> Logic { get; set; }
    }

    internal class Component
    {

        [JsonProperty("key")]
        public string Key { get; set; }

        [JsonProperty("values")]
        public Values Values { get; set; }
    }

    internal class Logic
    {
        [JsonProperty("key")]
        public string Key { get; set; }

        [JsonProperty("values")]
        public LogicValues LogicValues { get; set; }
    }

    internal class LogicValues
    {
        [JsonProperty("Node")]
        public List<List<List<int>>> Node { get; set; }

        //[JsonProperty("Distance")]
        //public int? Distance { get; set; }

        [JsonProperty("Type")]
        public string Type { get; set; }

        [JsonProperty("PatrolType")]
        public string PatrolType { get; set; }

        [JsonProperty("EnemyType")]
        public string EnemyType { get; set; }

        [JsonProperty("Speed")]
        public int? Speed { get; set; }

        [JsonProperty("ShowTime")]
        public int? ShowTime { get; set; }

        [JsonProperty("ParticleType")]
        public string ParticleType { get; set; }

        [JsonProperty("Stage")]
        public string Stage { get; set; }

        //[JsonProperty("Footstep")]
        //public int? Footstep { get; set; }

        [JsonProperty("Point")]
        public List<List<int?>> Point { get; set; }

        [JsonProperty("Message")]
        public object[][] Message { get; set; }
    }

    internal class Values
    {

        [JsonProperty("Position")]
        public int[] Position { get; set; }

        [JsonProperty("Scale")]
        public int[] Scale { get; set; }

        [JsonProperty("Rotation")]
        public float Rotation { get; set; }

        [JsonProperty("Texture")]
        public string Texture { get; set; }
}



    #endregion

}
