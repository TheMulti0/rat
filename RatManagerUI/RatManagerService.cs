using System;
using System.Reactive.Linq;
using Server.Interop;

namespace RatManagerUI
{
    internal class RatManagerService
    {
        public IObservable<int> ClientCount { get; }

        public RatManagerService()
        {
            IRatManager manager = new RatManager(4545);

            ClientCount = Observable
                .Interval(TimeSpan.FromMilliseconds(100))
                .Select(_ => manager.GetClientCount())
                .DistinctUntilChanged();
        }
    }
}
