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

            ZegoServerAssistant.GenerateTokenResult result = ZegoServerAssistant.ServerAssistant.GenerateToken04(3417014186, "999922222333333", "fa4b7e22b9c73dcdb6e7f7f116b9102a", 3600);
        }
    }
}
