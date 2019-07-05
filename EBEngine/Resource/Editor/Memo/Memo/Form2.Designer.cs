namespace Memo
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox_Y = new System.Windows.Forms.TextBox();
            this.SetNode = new System.Windows.Forms.Button();
            this.textBox_X = new System.Windows.Forms.TextBox();
            this.NodeX = new System.Windows.Forms.Label();
            this.NodeY = new System.Windows.Forms.Label();
            this.label_Title = new System.Windows.Forms.Label();
            this.label_Speed = new System.Windows.Forms.Label();
            this.label_Footstep = new System.Windows.Forms.Label();
            this.label_Distance = new System.Windows.Forms.Label();
            this.textBox_Speed = new System.Windows.Forms.TextBox();
            this.textBox_FootStep = new System.Windows.Forms.TextBox();
            this.textBox_Distance = new System.Windows.Forms.TextBox();
            this.button_Normal = new System.Windows.Forms.Button();
            this.button_Web = new System.Windows.Forms.Button();
            this.button_Bullet = new System.Windows.Forms.Button();
            this.button_Drugger = new System.Windows.Forms.Button();
            this.button_Bomber = new System.Windows.Forms.Button();
            this.checkedListBox_p_Type = new System.Windows.Forms.CheckedListBox();
            this.textBox_Point1_X = new System.Windows.Forms.TextBox();
            this.label_Point1 = new System.Windows.Forms.Label();
            this.label_Point2 = new System.Windows.Forms.Label();
            this.label_Point3 = new System.Windows.Forms.Label();
            this.label_Point4 = new System.Windows.Forms.Label();
            this.label_Point5 = new System.Windows.Forms.Label();
            this.textBox_Point2_X = new System.Windows.Forms.TextBox();
            this.textBox_Point3_X = new System.Windows.Forms.TextBox();
            this.textBox_Point4_X = new System.Windows.Forms.TextBox();
            this.textBox_Point5_X = new System.Windows.Forms.TextBox();
            this.textBox_Point1_Y = new System.Windows.Forms.TextBox();
            this.textBox_Point2_Y = new System.Windows.Forms.TextBox();
            this.textBox_Point3_Y = new System.Windows.Forms.TextBox();
            this.textBox_Point4_Y = new System.Windows.Forms.TextBox();
            this.textBox_Point5_Y = new System.Windows.Forms.TextBox();
            this.label_Rotation = new System.Windows.Forms.Label();
            this.textBox_Rotation = new System.Windows.Forms.TextBox();
            this.button_Rotation = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox_Y
            // 
            this.textBox_Y.Location = new System.Drawing.Point(53, 65);
            this.textBox_Y.Name = "textBox_Y";
            this.textBox_Y.Size = new System.Drawing.Size(75, 20);
            this.textBox_Y.TabIndex = 0;
            // 
            // SetNode
            // 
            this.SetNode.Location = new System.Drawing.Point(12, 95);
            this.SetNode.Name = "SetNode";
            this.SetNode.Size = new System.Drawing.Size(75, 23);
            this.SetNode.TabIndex = 1;
            this.SetNode.Text = "Set Node";
            this.SetNode.UseVisualStyleBackColor = true;
            this.SetNode.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setNodeButton_Click);
            // 
            // textBox_X
            // 
            this.textBox_X.Location = new System.Drawing.Point(53, 35);
            this.textBox_X.Name = "textBox_X";
            this.textBox_X.Size = new System.Drawing.Size(75, 20);
            this.textBox_X.TabIndex = 3;
            // 
            // NodeX
            // 
            this.NodeX.AutoSize = true;
            this.NodeX.Location = new System.Drawing.Point(12, 38);
            this.NodeX.Name = "NodeX";
            this.NodeX.Size = new System.Drawing.Size(43, 13);
            this.NodeX.TabIndex = 4;
            this.NodeX.Text = "Node X";
            // 
            // NodeY
            // 
            this.NodeY.AutoSize = true;
            this.NodeY.Location = new System.Drawing.Point(12, 68);
            this.NodeY.Name = "NodeY";
            this.NodeY.Size = new System.Drawing.Size(43, 13);
            this.NodeY.TabIndex = 5;
            this.NodeY.Text = "Node Y";
            // 
            // label_Title
            // 
            this.label_Title.AutoSize = true;
            this.label_Title.Location = new System.Drawing.Point(12, 9);
            this.label_Title.Name = "label_Title";
            this.label_Title.Size = new System.Drawing.Size(27, 13);
            this.label_Title.TabIndex = 6;
            this.label_Title.Text = "Title";
            // 
            // label_Speed
            // 
            this.label_Speed.AutoSize = true;
            this.label_Speed.Location = new System.Drawing.Point(179, 9);
            this.label_Speed.Name = "label_Speed";
            this.label_Speed.Size = new System.Drawing.Size(38, 13);
            this.label_Speed.TabIndex = 7;
            this.label_Speed.Text = "Speed";
            // 
            // label_Footstep
            // 
            this.label_Footstep.AutoSize = true;
            this.label_Footstep.Location = new System.Drawing.Point(179, 35);
            this.label_Footstep.Name = "label_Footstep";
            this.label_Footstep.Size = new System.Drawing.Size(50, 13);
            this.label_Footstep.TabIndex = 8;
            this.label_Footstep.Text = "FootStep";
            // 
            // label_Distance
            // 
            this.label_Distance.AutoSize = true;
            this.label_Distance.Location = new System.Drawing.Point(179, 65);
            this.label_Distance.Name = "label_Distance";
            this.label_Distance.Size = new System.Drawing.Size(49, 13);
            this.label_Distance.TabIndex = 9;
            this.label_Distance.Text = "Distance";
            // 
            // textBox_Speed
            // 
            this.textBox_Speed.Location = new System.Drawing.Point(228, 6);
            this.textBox_Speed.Name = "textBox_Speed";
            this.textBox_Speed.Size = new System.Drawing.Size(75, 20);
            this.textBox_Speed.TabIndex = 10;
            // 
            // textBox_FootStep
            // 
            this.textBox_FootStep.Location = new System.Drawing.Point(228, 32);
            this.textBox_FootStep.Name = "textBox_FootStep";
            this.textBox_FootStep.Size = new System.Drawing.Size(75, 20);
            this.textBox_FootStep.TabIndex = 11;
            // 
            // textBox_Distance
            // 
            this.textBox_Distance.Location = new System.Drawing.Point(228, 62);
            this.textBox_Distance.Name = "textBox_Distance";
            this.textBox_Distance.Size = new System.Drawing.Size(75, 20);
            this.textBox_Distance.TabIndex = 12;
            // 
            // button_Normal
            // 
            this.button_Normal.Location = new System.Drawing.Point(309, 4);
            this.button_Normal.Name = "button_Normal";
            this.button_Normal.Size = new System.Drawing.Size(55, 23);
            this.button_Normal.TabIndex = 13;
            this.button_Normal.Text = "Normal";
            this.button_Normal.UseVisualStyleBackColor = true;
            this.button_Normal.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setNormalButton_Click);
            // 
            // button_Web
            // 
            this.button_Web.Location = new System.Drawing.Point(309, 30);
            this.button_Web.Name = "button_Web";
            this.button_Web.Size = new System.Drawing.Size(55, 23);
            this.button_Web.TabIndex = 14;
            this.button_Web.Text = "Web";
            this.button_Web.UseVisualStyleBackColor = true;
            this.button_Web.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setWebButton_Click);
            // 
            // button_Bullet
            // 
            this.button_Bullet.Location = new System.Drawing.Point(309, 55);
            this.button_Bullet.Name = "button_Bullet";
            this.button_Bullet.Size = new System.Drawing.Size(55, 23);
            this.button_Bullet.TabIndex = 15;
            this.button_Bullet.Text = "Bullet";
            this.button_Bullet.UseVisualStyleBackColor = true;
            this.button_Bullet.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setBulletButton_Click);
            // 
            // button_Drugger
            // 
            this.button_Drugger.Location = new System.Drawing.Point(309, 80);
            this.button_Drugger.Name = "button_Drugger";
            this.button_Drugger.Size = new System.Drawing.Size(55, 23);
            this.button_Drugger.TabIndex = 16;
            this.button_Drugger.Text = "Defender";
            this.button_Drugger.UseVisualStyleBackColor = true;
            this.button_Drugger.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setDefenderButton_Click);
            // 
            // button_Bomber
            // 
            this.button_Bomber.Location = new System.Drawing.Point(309, 105);
            this.button_Bomber.Name = "button_Bomber";
            this.button_Bomber.Size = new System.Drawing.Size(55, 23);
            this.button_Bomber.TabIndex = 17;
            this.button_Bomber.Text = "Bomber";
            this.button_Bomber.UseVisualStyleBackColor = true;
            this.button_Bomber.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setBomberButton_Click);
            // 
            // checkedListBox_p_Type
            // 
            this.checkedListBox_p_Type.FormattingEnabled = true;
            this.checkedListBox_p_Type.Items.AddRange(new object[] {
            "SHUTTLE",
            "LINEAR"});
            this.checkedListBox_p_Type.Location = new System.Drawing.Point(182, 88);
            this.checkedListBox_p_Type.Name = "checkedListBox_p_Type";
            this.checkedListBox_p_Type.Size = new System.Drawing.Size(121, 34);
            this.checkedListBox_p_Type.TabIndex = 18;
            // 
            // textBox_Point1_X
            // 
            this.textBox_Point1_X.Location = new System.Drawing.Point(425, 6);
            this.textBox_Point1_X.Name = "textBox_Point1_X";
            this.textBox_Point1_X.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point1_X.TabIndex = 21;
            // 
            // label_Point1
            // 
            this.label_Point1.AutoSize = true;
            this.label_Point1.Location = new System.Drawing.Point(388, 9);
            this.label_Point1.Name = "label_Point1";
            this.label_Point1.Size = new System.Drawing.Size(37, 13);
            this.label_Point1.TabIndex = 22;
            this.label_Point1.Text = "Point1";
            // 
            // label_Point2
            // 
            this.label_Point2.AutoSize = true;
            this.label_Point2.Location = new System.Drawing.Point(388, 35);
            this.label_Point2.Name = "label_Point2";
            this.label_Point2.Size = new System.Drawing.Size(37, 13);
            this.label_Point2.TabIndex = 23;
            this.label_Point2.Text = "Point2";
            // 
            // label_Point3
            // 
            this.label_Point3.AutoSize = true;
            this.label_Point3.Location = new System.Drawing.Point(388, 60);
            this.label_Point3.Name = "label_Point3";
            this.label_Point3.Size = new System.Drawing.Size(37, 13);
            this.label_Point3.TabIndex = 24;
            this.label_Point3.Text = "Point3";
            // 
            // label_Point4
            // 
            this.label_Point4.AutoSize = true;
            this.label_Point4.Location = new System.Drawing.Point(388, 85);
            this.label_Point4.Name = "label_Point4";
            this.label_Point4.Size = new System.Drawing.Size(37, 13);
            this.label_Point4.TabIndex = 25;
            this.label_Point4.Text = "Point4";
            // 
            // label_Point5
            // 
            this.label_Point5.AutoSize = true;
            this.label_Point5.Location = new System.Drawing.Point(388, 109);
            this.label_Point5.Name = "label_Point5";
            this.label_Point5.Size = new System.Drawing.Size(37, 13);
            this.label_Point5.TabIndex = 26;
            this.label_Point5.Text = "Point5";
            // 
            // textBox_Point2_X
            // 
            this.textBox_Point2_X.Location = new System.Drawing.Point(425, 32);
            this.textBox_Point2_X.Name = "textBox_Point2_X";
            this.textBox_Point2_X.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point2_X.TabIndex = 27;
            // 
            // textBox_Point3_X
            // 
            this.textBox_Point3_X.Location = new System.Drawing.Point(425, 57);
            this.textBox_Point3_X.Name = "textBox_Point3_X";
            this.textBox_Point3_X.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point3_X.TabIndex = 28;
            // 
            // textBox_Point4_X
            // 
            this.textBox_Point4_X.Location = new System.Drawing.Point(425, 82);
            this.textBox_Point4_X.Name = "textBox_Point4_X";
            this.textBox_Point4_X.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point4_X.TabIndex = 29;
            // 
            // textBox_Point5_X
            // 
            this.textBox_Point5_X.Location = new System.Drawing.Point(425, 107);
            this.textBox_Point5_X.Name = "textBox_Point5_X";
            this.textBox_Point5_X.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point5_X.TabIndex = 30;
            // 
            // textBox_Point1_Y
            // 
            this.textBox_Point1_Y.Location = new System.Drawing.Point(469, 6);
            this.textBox_Point1_Y.Name = "textBox_Point1_Y";
            this.textBox_Point1_Y.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point1_Y.TabIndex = 31;
            // 
            // textBox_Point2_Y
            // 
            this.textBox_Point2_Y.Location = new System.Drawing.Point(469, 35);
            this.textBox_Point2_Y.Name = "textBox_Point2_Y";
            this.textBox_Point2_Y.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point2_Y.TabIndex = 32;
            // 
            // textBox_Point3_Y
            // 
            this.textBox_Point3_Y.Location = new System.Drawing.Point(469, 57);
            this.textBox_Point3_Y.Name = "textBox_Point3_Y";
            this.textBox_Point3_Y.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point3_Y.TabIndex = 33;
            // 
            // textBox_Point4_Y
            // 
            this.textBox_Point4_Y.Location = new System.Drawing.Point(469, 82);
            this.textBox_Point4_Y.Name = "textBox_Point4_Y";
            this.textBox_Point4_Y.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point4_Y.TabIndex = 34;
            // 
            // textBox_Point5_Y
            // 
            this.textBox_Point5_Y.Location = new System.Drawing.Point(469, 106);
            this.textBox_Point5_Y.Name = "textBox_Point5_Y";
            this.textBox_Point5_Y.Size = new System.Drawing.Size(38, 20);
            this.textBox_Point5_Y.TabIndex = 35;
            // 
            // label_Rotation
            // 
            this.label_Rotation.AutoSize = true;
            this.label_Rotation.Location = new System.Drawing.Point(522, 9);
            this.label_Rotation.Name = "label_Rotation";
            this.label_Rotation.Size = new System.Drawing.Size(47, 13);
            this.label_Rotation.TabIndex = 36;
            this.label_Rotation.Text = "Rotation";
            // 
            // textBox_Rotation
            // 
            this.textBox_Rotation.Location = new System.Drawing.Point(575, 4);
            this.textBox_Rotation.Name = "textBox_Rotation";
            this.textBox_Rotation.Size = new System.Drawing.Size(38, 20);
            this.textBox_Rotation.TabIndex = 37;
            // 
            // button_Rotation
            // 
            this.button_Rotation.Location = new System.Drawing.Point(525, 28);
            this.button_Rotation.Name = "button_Rotation";
            this.button_Rotation.Size = new System.Drawing.Size(88, 23);
            this.button_Rotation.TabIndex = 38;
            this.button_Rotation.Text = "Rotation";
            this.button_Rotation.UseVisualStyleBackColor = true;
            this.button_Rotation.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setLaserRotationButton_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(309, 132);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(55, 23);
            this.button1.TabIndex = 39;
            this.button1.Text = "Anti";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.setAntiButton_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(646, 160);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.button_Rotation);
            this.Controls.Add(this.textBox_Rotation);
            this.Controls.Add(this.label_Rotation);
            this.Controls.Add(this.textBox_Point5_Y);
            this.Controls.Add(this.textBox_Point4_Y);
            this.Controls.Add(this.textBox_Point3_Y);
            this.Controls.Add(this.textBox_Point2_Y);
            this.Controls.Add(this.textBox_Point1_Y);
            this.Controls.Add(this.textBox_Point5_X);
            this.Controls.Add(this.textBox_Point4_X);
            this.Controls.Add(this.textBox_Point3_X);
            this.Controls.Add(this.textBox_Point2_X);
            this.Controls.Add(this.label_Point5);
            this.Controls.Add(this.label_Point4);
            this.Controls.Add(this.label_Point3);
            this.Controls.Add(this.label_Point2);
            this.Controls.Add(this.label_Point1);
            this.Controls.Add(this.textBox_Point1_X);
            this.Controls.Add(this.checkedListBox_p_Type);
            this.Controls.Add(this.button_Bomber);
            this.Controls.Add(this.button_Drugger);
            this.Controls.Add(this.button_Bullet);
            this.Controls.Add(this.button_Web);
            this.Controls.Add(this.button_Normal);
            this.Controls.Add(this.textBox_Distance);
            this.Controls.Add(this.textBox_FootStep);
            this.Controls.Add(this.textBox_Speed);
            this.Controls.Add(this.label_Distance);
            this.Controls.Add(this.label_Footstep);
            this.Controls.Add(this.label_Speed);
            this.Controls.Add(this.label_Title);
            this.Controls.Add(this.NodeY);
            this.Controls.Add(this.NodeX);
            this.Controls.Add(this.textBox_X);
            this.Controls.Add(this.SetNode);
            this.Controls.Add(this.textBox_Y);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form2";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_Y;
        private System.Windows.Forms.Button SetNode;
        private System.Windows.Forms.TextBox textBox_X;
        private System.Windows.Forms.Label NodeX;
        private System.Windows.Forms.Label NodeY;
        private System.Windows.Forms.Label label_Title;
        private System.Windows.Forms.Label label_Speed;
        private System.Windows.Forms.Label label_Footstep;
        private System.Windows.Forms.Label label_Distance;
        private System.Windows.Forms.TextBox textBox_Speed;
        private System.Windows.Forms.TextBox textBox_FootStep;
        private System.Windows.Forms.TextBox textBox_Distance;
        private System.Windows.Forms.Button button_Normal;
        private System.Windows.Forms.Button button_Web;
        private System.Windows.Forms.Button button_Bullet;
        private System.Windows.Forms.Button button_Drugger;
        private System.Windows.Forms.Button button_Bomber;
        private System.Windows.Forms.CheckedListBox checkedListBox_p_Type;
        private System.Windows.Forms.TextBox textBox_Point1_X;
        private System.Windows.Forms.Label label_Point1;
        private System.Windows.Forms.Label label_Point2;
        private System.Windows.Forms.Label label_Point3;
        private System.Windows.Forms.Label label_Point4;
        private System.Windows.Forms.Label label_Point5;
        private System.Windows.Forms.TextBox textBox_Point2_X;
        private System.Windows.Forms.TextBox textBox_Point3_X;
        private System.Windows.Forms.TextBox textBox_Point4_X;
        private System.Windows.Forms.TextBox textBox_Point5_X;
        private System.Windows.Forms.TextBox textBox_Point1_Y;
        private System.Windows.Forms.TextBox textBox_Point2_Y;
        private System.Windows.Forms.TextBox textBox_Point3_Y;
        private System.Windows.Forms.TextBox textBox_Point4_Y;
        private System.Windows.Forms.TextBox textBox_Point5_Y;
        private System.Windows.Forms.Label label_Rotation;
        private System.Windows.Forms.TextBox textBox_Rotation;
        private System.Windows.Forms.Button button_Rotation;
        private System.Windows.Forms.Button button1;
    }
}