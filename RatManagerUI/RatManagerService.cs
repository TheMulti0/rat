using System;
using System.Reactive.Linq;
using Server.Interop;

namespace RatManagerUI
{
    internal class RatManagerService
    {
        public IRatManager _manager;
        public IObservable<int> ClientCount { get; }

        public RatManagerService()
        {
            _manager = new RatManager(4545);

            ClientCount = Observable
                .Interval(TimeSpan.FromMilliseconds(100))
                .Select(_ => _manager.GetClientCount())
                .DistinctUntilChanged();
        }
    }
}
