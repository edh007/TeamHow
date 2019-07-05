namespace Memo
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pressAfterMappingToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.panel_picture = new System.Windows.Forms.Panel();
            this.pictureBox_Laser = new System.Windows.Forms.PictureBox();
            this.pictureBox_Enemy = new System.Windows.Forms.PictureBox();
            this.pictureBox_Node = new System.Windows.Forms.PictureBox();
            this.pictureBox_Glass = new System.Windows.Forms.PictureBox();
            this.pictureBox_Target = new System.Windows.Forms.PictureBox();
            this.pictureBox_Exit = new System.Windows.Forms.PictureBox();
            this.pictureBox_Wall = new System.Windows.Forms.PictureBox();
            this.pictureBox_Rect = new System.Windows.Forms.PictureBox();
            this.pictureBox_Turret = new System.Windows.Forms.PictureBox();
            this.pictureBox_Fog = new System.Windows.Forms.PictureBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.panel_map = new System.Windows.Forms.Panel();
            this.panel_display = new System.Windows.Forms.Panel();
            this.menuStrip1.SuspendLayout();
            this.panel_picture.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Laser)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Enemy)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Node)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Glass)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Target)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Exit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Wall)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Rect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Turret)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Fog)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.panel_display.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Append;
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Left;
            this.textBox1.Location = new System.Drawing.Point(0, 24);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(196, 855);
            this.textBox1.TabIndex = 1;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem,
            this.pressAfterMappingToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(4, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(1473, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFileToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            this.menuToolStripMenuItem.ShortcutKeyDisplayString = "";
            this.menuToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.menuToolStripMenuItem.Text = "파일";
            this.menuToolStripMenuItem.Click += new System.EventHandler(this.menuToolStripMenuItem_Click);
            // 
            // openFileToolStripMenuItem
            // 
            this.openFileToolStripMenuItem.Name = "openFileToolStripMenuItem";
            this.openFileToolStripMenuItem.ShortcutKeyDisplayString = "";
            this.openFileToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openFileToolStripMenuItem.Size = new System.Drawing.Size(248, 22);
            this.openFileToolStripMenuItem.Text = "열기";
            this.openFileToolStripMenuItem.Click += new System.EventHandler(this.openFileToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(248, 22);
            this.saveToolStripMenuItem.Text = "저장";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(248, 22);
            this.saveAsToolStripMenuItem.Text = "다른 이름으로 저장";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(248, 22);
            this.exitToolStripMenuItem.Text = "끝내기";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // pressAfterMappingToolStripMenuItem
            // 
            this.pressAfterMappingToolStripMenuItem.Name = "pressAfterMappingToolStripMenuItem";
            this.pressAfterMappingToolStripMenuItem.Size = new System.Drawing.Size(126, 20);
            this.pressAfterMappingToolStripMenuItem.Text = "Press After Mapping";
            this.pressAfterMappingToolStripMenuItem.Click += new System.EventHandler(this.pressAfterMappingToolStripMenuItem_Click);
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Left;
            this.treeView1.Location = new System.Drawing.Point(196, 24);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(163, 855);
            this.treeView1.TabIndex = 3;
            // 
            // panel_picture
            // 
            this.panel_picture.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel_picture.Controls.Add(this.pictureBox_Laser);
            this.panel_picture.Controls.Add(this.pictureBox_Enemy);
            this.panel_picture.Controls.Add(this.pictureBox_Node);
            this.panel_picture.Controls.Add(this.pictureBox_Glass);
            this.panel_picture.Controls.Add(this.pictureBox_Target);
            this.panel_picture.Controls.Add(this.pictureBox_Exit);
            this.panel_picture.Controls.Add(this.pictureBox_Wall);
            this.panel_picture.Controls.Add(this.pictureBox_Rect);
            this.panel_picture.Controls.Add(this.pictureBox_Turret);
            this.panel_picture.Controls.Add(this.pictureBox_Fog);
            this.panel_picture.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel_picture.Location = new System.Drawing.Point(1423, 24);
            this.panel_picture.Name = "panel_picture";
            this.panel_picture.Size = new System.Drawing.Size(50, 855);
            this.panel_picture.TabIndex = 0;
            // 
            // pictureBox_Laser
            // 
            this.pictureBox_Laser.Image = global::Memo.Properties.Resources.Laser;
            this.pictureBox_Laser.Location = new System.Drawing.Point(3, 449);
            this.pictureBox_Laser.Name = "pictureBox_Laser";
            this.pictureBox_Laser.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Laser.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Laser.TabIndex = 9;
            this.pictureBox_Laser.TabStop = false;
            this.pictureBox_Laser.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Laser_MouseClick);
            // 
            // pictureBox_Enemy
            // 
            this.pictureBox_Enemy.Image = global::Memo.Properties.Resources.Enemy;
            this.pictureBox_Enemy.Location = new System.Drawing.Point(4, 400);
            this.pictureBox_Enemy.Name = "pictureBox_Enemy";
            this.pictureBox_Enemy.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Enemy.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Enemy.TabIndex = 8;
            this.pictureBox_Enemy.TabStop = false;
            this.pictureBox_Enemy.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Enemy_MouseClick);
            // 
            // pictureBox_Node
            // 
            this.pictureBox_Node.Image = global::Memo.Properties.Resources.Node;
            this.pictureBox_Node.Location = new System.Drawing.Point(4, 351);
            this.pictureBox_Node.Name = "pictureBox_Node";
            this.pictureBox_Node.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Node.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Node.TabIndex = 7;
            this.pictureBox_Node.TabStop = false;
            this.pictureBox_Node.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Node_MouseClick);
            // 
            // pictureBox_Glass
            // 
            this.pictureBox_Glass.Image = global::Memo.Properties.Resources.Radar;
            this.pictureBox_Glass.Location = new System.Drawing.Point(4, 302);
            this.pictureBox_Glass.Name = "pictureBox_Glass";
            this.pictureBox_Glass.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Glass.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Glass.TabIndex = 6;
            this.pictureBox_Glass.TabStop = false;
            this.pictureBox_Glass.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Glass_MouseClick);
            // 
            // pictureBox_Target
            // 
            this.pictureBox_Target.Image = global::Memo.Properties.Resources.Target;
            this.pictureBox_Target.Location = new System.Drawing.Point(4, 252);
            this.pictureBox_Target.Name = "pictureBox_Target";
            this.pictureBox_Target.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Target.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Target.TabIndex = 5;
            this.pictureBox_Target.TabStop = false;
            this.pictureBox_Target.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Target_MouseClick);
            // 
            // pictureBox_Exit
            // 
            this.pictureBox_Exit.Image = global::Memo.Properties.Resources.Exit;
            this.pictureBox_Exit.Location = new System.Drawing.Point(4, 203);
            this.pictureBox_Exit.Name = "pictureBox_Exit";
            this.pictureBox_Exit.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Exit.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Exit.TabIndex = 4;
            this.pictureBox_Exit.TabStop = false;
            this.pictureBox_Exit.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Exit_MouseClick);
            // 
            // pictureBox_Wall
            // 
            this.pictureBox_Wall.Image = global::Memo.Properties.Resources.Wall;
            this.pictureBox_Wall.Location = new System.Drawing.Point(4, 153);
            this.pictureBox_Wall.Name = "pictureBox_Wall";
            this.pictureBox_Wall.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Wall.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Wall.TabIndex = 3;
            this.pictureBox_Wall.TabStop = false;
            this.pictureBox_Wall.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Wall_MouseClick);
            // 
            // pictureBox_Rect
            // 
            this.pictureBox_Rect.Image = global::Memo.Properties.Resources.Rect;
            this.pictureBox_Rect.Location = new System.Drawing.Point(4, 103);
            this.pictureBox_Rect.Name = "pictureBox_Rect";
            this.pictureBox_Rect.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Rect.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Rect.TabIndex = 2;
            this.pictureBox_Rect.TabStop = false;
            this.pictureBox_Rect.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Rect_MouseClick);
            // 
            // pictureBox_Turret
            // 
            this.pictureBox_Turret.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox_Turret.Image")));
            this.pictureBox_Turret.Location = new System.Drawing.Point(4, 53);
            this.pictureBox_Turret.Name = "pictureBox_Turret";
            this.pictureBox_Turret.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Turret.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Turret.TabIndex = 1;
            this.pictureBox_Turret.TabStop = false;
            this.pictureBox_Turret.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Turret_MouseClick);
            // 
            // pictureBox_Fog
            // 
            this.pictureBox_Fog.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox_Fog.Image")));
            this.pictureBox_Fog.Location = new System.Drawing.Point(4, 3);
            this.pictureBox_Fog.Name = "pictureBox_Fog";
            this.pictureBox_Fog.Size = new System.Drawing.Size(34, 43);
            this.pictureBox_Fog.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_Fog.TabIndex = 0;
            this.pictureBox_Fog.TabStop = false;
            this.pictureBox_Fog.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_Fog_MouseClick);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(359, 857);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Padding = new System.Windows.Forms.Padding(1, 0, 12, 0);
            this.statusStrip1.Size = new System.Drawing.Size(1064, 22);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(0, 17);
            // 
            // panel_map
            // 
            this.panel_map.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel_map.BackColor = System.Drawing.SystemColors.Window;
            this.panel_map.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel_map.Location = new System.Drawing.Point(8, 10);
            this.panel_map.Name = "panel_map";
            this.panel_map.Size = new System.Drawing.Size(1024, 768);
            this.panel_map.TabIndex = 4;
            this.panel_map.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.panel_map.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel_map_MouseClick);
            this.panel_map.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel_map_MouseMove);
            // 
            // panel_display
            // 
            this.panel_display.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel_display.BackColor = System.Drawing.Color.Silver;
            this.panel_display.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel_display.Controls.Add(this.panel_map);
            this.panel_display.Location = new System.Drawing.Point(363, 30);
            this.panel_display.Name = "panel_display";
            this.panel_display.Size = new System.Drawing.Size(1034, 778);
            this.panel_display.TabIndex = 2;
            this.panel_display.MouseClick += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseClick);
            this.panel_display.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseMove);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1473, 879);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.panel_picture);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.panel_display);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Tools";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel_picture.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Laser)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Enemy)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Node)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Glass)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Target)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Exit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Wall)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Rect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Turret)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Fog)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.panel_display.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.Panel panel_picture;
        private System.Windows.Forms.PictureBox pictureBox_Turret;
        private System.Windows.Forms.PictureBox pictureBox_Fog;
        private System.Windows.Forms.PictureBox pictureBox_Rect;
        private System.Windows.Forms.ToolStripMenuItem pressAfterMappingToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox_Wall;
        private System.Windows.Forms.PictureBox pictureBox_Target;
        private System.Windows.Forms.PictureBox pictureBox_Exit;
        private System.Windows.Forms.PictureBox pictureBox_Glass;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.PictureBox pictureBox_Node;
        private System.Windows.Forms.PictureBox pictureBox_Enemy;
        private System.Windows.Forms.Panel panel_map;
        private System.Windows.Forms.Panel panel_display;
        private System.Windows.Forms.PictureBox pictureBox_Laser;
    }
}

