using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Memo
{
    public partial class Form2 : Form
    {
        private IMyInterface frm = null;
        public List<int> node;
        public bool checkEnd = false;
        public List<List<int?>> point = new List<List<int?>>();
        //public List<Point> point;
        public string patrol_type = "";
        //public Point p = new Point();
        public List<int> rotation = new List<int>();
        

        public Form2(IMyInterface frm)
        {
            InitializeComponent();
            this.frm = frm;
            node = new List<int>();
        }

        public void ChangeTitle(string text)
        {
            label_Title.Text = text;
        }

        public void setNodeButton_Click(object sender, MouseEventArgs e)
        {
            if (textBox_X.Text == "" || textBox_Y.Text == "")
            {
                MessageBox.Show("ERROR!");
                return;
            }

            node.Add(int.Parse(textBox_X.Text));
            node.Add(int.Parse(textBox_Y.Text));

            frm.SetData(node);

            checkEnd = true;
            
            this.Close();
        }

        private void SetRotation()
        {
            if (textBox_Rotation.Text != "")
            {
                int r = int.Parse(textBox_Rotation.Text);
                rotation.Add(r);
            }
        }

        public void setLaserRotationButton_Click(object sender, MouseEventArgs e)
        {
            if (textBox_X.Text != "" && textBox_Y.Text != "")
            {
                MessageBox.Show("Delete Node X & Y");
                return;
            }

            if (textBox_Speed.Text != "")
            {
                MessageBox.Show("Delete the whole Value without Rotation.\nIf you made enemy, please click enemy type.");
                return;
            }

            SetRotation();
            checkEnd = true;
            frm.SetRotation(rotation);
            this.Close();
        }

        private void SetEnemy(int type)
        {
            if (textBox_X.Text != "" && textBox_Y.Text != "")
            {
                MessageBox.Show("Delete Node X & Y");
                return;
            }

            if (textBox_Speed.Text == "")
            {
                MessageBox.Show("Enter the whole Value");
                return;
            }

            for(int i = 0; i < this.checkedListBox_p_Type.Items.Count; i++)
            {
                if (this.checkedListBox_p_Type.GetItemChecked(i))
                    patrol_type = this.checkedListBox_p_Type.Items[i].ToString();
            }

            int ptrl = 100;
            if(patrol_type == "")
            {
                MessageBox.Show("Enter the whole Value");
                return;
            }
            else if(patrol_type == "SHUTTLE")
                ptrl = 0;
            else if (patrol_type == "LINEAR")
                ptrl = 1;

            if (textBox_Point1_X.Text != "" && textBox_Point1_Y.Text != "")
            {
                List<int?> p = new List<int?>();
                p.Add(int.Parse(textBox_Point1_X.Text));
                p.Add(int.Parse(textBox_Point1_Y.Text));
                point.Add(p);
            }
            if (textBox_Point2_X.Text != "" && textBox_Point2_Y.Text != "")
            {
                List<int?> p = new List<int?>();
                p.Add(int.Parse(textBox_Point2_X.Text));
                p.Add(int.Parse(textBox_Point2_Y.Text));
                point.Add(p);
            }
            if (textBox_Point3_X.Text != "" && textBox_Point3_Y.Text != "")
            {
                List<int?> p = new List<int?>();
                p.Add(int.Parse(textBox_Point3_X.Text));
                p.Add(int.Parse(textBox_Point3_Y.Text));
                point.Add(p);
            }
            if (textBox_Point4_X.Text != "" && textBox_Point4_Y.Text != "")
            {
                List<int?> p = new List<int?>();
                p.Add(int.Parse(textBox_Point4_X.Text));
                p.Add(int.Parse(textBox_Point4_Y.Text));
                point.Add(p);
            }
            if (textBox_Point5_X.Text != "" && textBox_Point5_Y.Text != "")
            {
                List<int?> p = new List<int?>();
                p.Add(int.Parse(textBox_Point5_X.Text));
                p.Add(int.Parse(textBox_Point5_Y.Text));
                point.Add(p);
            }

            node.Add(int.Parse(textBox_Speed.Text));
            //node.Add(int.Parse(textBox_FootStep.Text));
            //node.Add(int.Parse(textBox_Distance.Text));
            node.Add(type);
            node.Add(ptrl);

            if (textBox_Rotation.Text != "")
            {
                int r = int.Parse(textBox_Rotation.Text);
                node.Add(r);
            }

            frm.SetEnemy(node, point);

            checkEnd = true;
            this.Close();
        }

        public void setNormalButton_Click(object sender, MouseEventArgs e)
        {
            SetEnemy(0);
        }

        public void setWebButton_Click(object sender, MouseEventArgs e)
        {
            SetEnemy(1);
        }

        public void setBulletButton_Click(object sender, MouseEventArgs e)
        {
            SetEnemy(2);
        }

        public void setDefenderButton_Click(object sender, MouseEventArgs e)
        {
            SetEnemy(3);
        }

        public void setBomberButton_Click(object sender, MouseEventArgs e)
        {
            SetEnemy(4);
        }

        public void setAntiButton_Click(object sender, MouseEventArgs e)
        {
            SetEnemy(5);
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }
    }
}
