#ifndef __SESSION_HPP__
#define __SESSION_HPP__

class Session
{
public:
	struct Exception
	{
		const char *call;
		int code;        // errno
		Exception(const char *call, int code = 0) : call(call), code(code) {}
		void Write() const;
	};
	
	Session(const WhosOn::LogonEventAdapter *adapter, Options *opts);
	~Session();
	
	void Setup();
	void Start();
	
	static void Done() { done = true; }
	static void SignalHandler(int sig);
	
private:
	const WhosOn::LogonEventAdapter *adapter;
	Options *opts;
	volatile static bool done;
};

#endif // __SESSION_HPP__
