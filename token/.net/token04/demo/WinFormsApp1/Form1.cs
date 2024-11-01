using ZegoServerAssistant;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Dictionary<string, object> payload = new Dictionary<string, object>();
            payload["room_id"] = "0002";
            List<string> stream_id_list = new List<string>();
            stream_id_list.Add("0002");
            Dictionary<string, object> privilege = new Dictionary<string, object>();
            privilege["1"] = 1;
            privilege["2"] = 2;
            payload["stream_id_list"] = stream_id_list;
            payload["privilege"] = privilege;
            string strPayload = JsonConvert.SerializeObject(payload);

            ZegoServerAssistant.GenerateTokenResult result = ZegoServerAssistant.ServerAssistant.GenerateToken04(123, "456", "", 3600, strPayload);


            ZegoServerAssistant.GenerateTokenResult rtc_result = ZegoServerAssistant.ServerAssistant.GenerateToken04(123, "456", "", 3600, strPayload);
        }
    }
}
