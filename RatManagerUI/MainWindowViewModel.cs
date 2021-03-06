using System;
using PropertyChanged.SourceGenerator;

namespace RatManagerUI
{
    internal partial class MainWindowViewModel
    {
        public readonly RatManagerService _service = new();

        [Notify]
        private int _clientCount;

        public MainWindowViewModel()
        {
            _service.ClientCount.Subscribe(i => ClientCount = i);
        }
    }
}
