simple Generator
{
    parameters:
        volatile double generationInterval; // sec
        int packetByteSize;
        @display("i=block/source");
    gates:
        input inInstructions @directIn;
        output out;
}

simple Queue
{
    parameters:
        int bufferSize;
        @display("i=block/queue;q=buffer");
    gates:
        input in;
        output out;
}

simple Sink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}

simple TransportTx
{
    parameters:
        int bufferSize;
        @display("i=block/queue;queue=buffer_tx");
    gates:
        input toApp;
        inout toOut;
        output outInstructions @directOut;
}

simple TransportRx
{
    parameters:
        int bufferSize;
        @display("i=block/queue;queue=buffer_rx"); // Elimina el espacio en blanco antes de "queue"
    gates:
        output toApp;
        inout toOut;
}



module NodeTx
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
    submodules:
        gen: Generator {
            parameters:
                @display("p=75,50");
        }
        traTx: TransportTx {
            parameters:
                @display("p=75,190");
        }
    connections:
        in --> traTx.toOut$i;
        traTx.toOut$o --> out;
        gen.out --> traTx.toApp;
        traTx.outInstructions --> gen.inInstructions;
}
module NodeRx
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
    submodules:
        sink: Sink {
            parameters:
                @display("p=75,50");
        }
        traRx: TransportRx {
            parameters:
                @display("p=75,190");
        }
    connections:
        in --> traRx.toOut$i;
        //case study 1:
    	traRx.toApp --> {  datarate = 0.5Mbps;  }  --> sink.in;
		//case study 2:
    	//traRx.toApp --> {  datarate = 1Mbps;  }  --> sink.in;
    	traRx.toOut$o --> out; 	
}



network Network
{
    @display("bgl=2");
    submodules:
        nodeTx: NodeTx {
            @display("p=30,30");
        }
        queue: Queue {	
            @display("p=130,30");
        }
        queue2: Queue {
            @display("p=130,120");
        }
        nodeRx: NodeRx {
            @display("p=230,30");
        }
    connections:
        nodeTx.out --> {  datarate = 1Mbps; delay = 100us;  } --> queue.in;
        //case study 1;
        queue.out --> {  datarate = 1Mbps; delay = 100us;  } --> nodeRx.in;
        //case study 2;
        //queue.out --> {  datarate = 0.5Mbps; delay = 100us;  } --> nodeRx.in;
        nodeRx.out --> queue2.in;
        queue2.out --> nodeTx.in;
} 
