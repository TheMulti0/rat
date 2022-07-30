using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Input;
using PropertyChanged.SourceGenerator;
using Server.Interop;

namespace RatManagerUI
{
    internal partial class MainWindowViewModel
    {
        private readonly RatManagerService _service = new();

        [Notify]
        private int _clientCount;

        [Notify] 
        private List<ClientInfo>? _clients;

        public ICommand RefreshCommand { get; set; }

        public MainWindowViewModel()
        {
            _service.ClientCount.Subscribe(i => ClientCount = i);
            _service.Clients.Subscribe(infos => Clients = infos.ToList());

            RefreshCommand = new RefreshCommand(_service);
        }
    }
}
