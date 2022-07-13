using Server.Interop;

namespace RatManagerUI
{
    public partial class Form1 : Form
    {
        private readonly RatManager _ratManager;

        public Form1()
        {
            InitializeComponent();
            _ratManager = new RatManager(4545);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _ratManager.Send(0, MessageType.Chat, "cmd.exe".Select(c => (byte)c));
        }
    }
}