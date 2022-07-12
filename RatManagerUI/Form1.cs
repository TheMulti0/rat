using Server.Interop;

namespace RatManagerUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            var ratManager = new RatManager(4545);
            await Task.Delay(1000);
            var clientCount = ratManager.GetClientCount();
            Console.WriteLine();
        }
    }
}