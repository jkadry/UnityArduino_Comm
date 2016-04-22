import praw
import time

r = praw.Reddit(user_agent = "SayWhatAgain by /u/edewede")
print("Loggin in...")
r.login()

words_to_match = ["What?", "What??"]
cache = []

def run_bot():
    print("Grabbing subreddit...")
    subreddit = r.get_subreddit("test")
    comments = subreddit.get_comments(limit=100)
    for comment in comments:
        comment_text = comment.body.lower()
        isMatch = any(string in comment_text for string in words_to_match)
        if comment.id not in cache and isMatch:
            comment.reply('Say "what" again. Say "what" again, I dare you, I double dare you motherfucker, say "what" one more Goddamn time!')
            print("Reply succesful")
            cache.append(comment.id)
            print("Comments loop finished")

while True:
    run_bot()
    time.sleep(10)