class Flag{
	public:
		Flag();
		void set();
		void clear();
		void wait();
	private:
		bool flag_;
		std::mutex mutex_;
		std::condition_variable cond_var_;

};