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
using System.Collections;

namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Dictionary<string, object> payload = new Dictionary<string, object>();
            payload["room_id"] = "123456";
            List<string> stream_id_list = new List<string>();
            stream_id_list.Add("1111");
            Dictionary<string, object> privilege = new Dictionary<string, object>();
            privilege["1"] = 1;
            privilege["2"] = 2;
            payload["stream_id_list"] = stream_id_list;
            payload["privilege"] = privilege;
            string strPayload = JsonConvert.SerializeObject(payload);

            ZegoServerAssistant.GenerateTokenResult result = ZegoServerAssistant.ServerAssistant.GenerateToken04(1, "999922222333333", "12345678900987654321123456789012", 3600, strPayload);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
