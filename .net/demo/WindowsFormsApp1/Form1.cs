using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Security.Cryptography;
using ZegoServerAssistant;
using Newtonsoft.Json;

namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Dictionary<int, int> privilege = new Dictionary<int, int>();
            privilege[1] = 1;
            privilege[2] = 1;

            ZegoServerAssistant.GenerateTokenResult result = ZegoServerAssistant.ServerAssistant.GenerateToken(2913569222, "111", "222", privilege, "b0d996aecc46ad51600ea853bb378c18", 3600);
        }
    }
}
