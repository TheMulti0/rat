using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace RatManagerUI
{
    internal class RefreshCommand : ICommand
    {
        private readonly RatManagerService _service;

        public RefreshCommand(RatManagerService service)
        {
            _service = service;
        }

        public bool CanExecute(object? parameter)
        {
            return true;
        }

        public void Execute(object? parameter)
        {
            _service.Refresh();
        }

        public event EventHandler? CanExecuteChanged;
    }
}
