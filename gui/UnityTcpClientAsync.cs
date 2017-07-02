using UnityEngine;
using System;

public abstract class UnityTcpClientAsync : MonoBehaviour
{
    protected TcpClientAsync tcpClient = null;
    private bool run = false;
    private float timer = 0;
    private bool start = false;
    private float timeout;

    protected void Init(float t = 3)
    {
        tcpClient = new TcpClientAsync();
        timeout = t;
    }

    void Update()
    {
        if (run)
        {
            if (tcpClient.receiveStatus)
            {
                tcpClient.receiveStatus = false;
                string[] commands = tcpClient.getData().Split('\n');
                foreach (string cmd in commands)
                    OnReceive(cmd);
                tcpClient.Receive();
            }
            if (tcpClient.sendStatus)
            {
                tcpClient.sendStatus = false;
                OnSend(tcpClient.getSend());
            }
            if (!tcpClient.connectStatus)
                OnDisconnect();
        }
        else if (!run && tcpClient != null && tcpClient.connectStatus)
        {
            run = true;
            tcpClient.Receive();
            OnConnect();
        }
        else if (!run && tcpClient != null && !tcpClient.connectStatus && start)
        {
            timer += Time.deltaTime;
            if (timer > timeout)
            {
                timer = 0;
                start = false;
                OnError();
            }
        }
    }

    public void Connect(string ip, int port)
    {
        if (!start)
        {
            tcpClient.Connect(ip, port);
            start = true;
        }
    }

    public void Send(string data)
    {
        if (start)
        tcpClient.Send(data);
    }

    public void Disconnect()
    {
        if (tcpClient != null)
        {
            start = false;
            run = false;
            timer = 0;
            tcpClient.Disconnect();
        }
    }

    abstract public void OnConnect(params object[] p);
    abstract public void OnReceive(params object[] p);
    abstract public void OnSend(params object[] p);
    abstract public void OnError(params object[] p);
    abstract public void OnDisconnect(params object[] p);
}
