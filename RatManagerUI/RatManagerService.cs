using System;
using System.Collections.Generic;
using System.Reactive;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using Server.Interop;

namespace RatManagerUI
{
    internal class RatManagerService
    {
        private readonly IRatManager _manager;
        private readonly Subject<Unit> _refresh;

        public IObservable<int> ClientCount { get; }
        public IObservable<IEnumerable<ClientInfo>> Clients { get; }

        public RatManagerService()
        {
            _manager = new RatManager(4545);
            _refresh = new Subject<Unit>();

            var timer = Observable
                .Interval(TimeSpan.FromMilliseconds(1000000))
                .Publish()
                .RefCount()
                .Select(_ => Unit.Default)
                .Merge(_refresh);

            ClientCount = timer
                .Select(_ => _manager.GetClientCount())
                .DistinctUntilChanged();

            Clients = timer
                .Select(_ => _manager.GetClients())
                .DistinctUntilChanged();
        }

        public void Refresh()
        {
            _refresh.OnNext(Unit.Default);
        }
    }
}
