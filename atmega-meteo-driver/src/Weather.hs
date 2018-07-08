module Weather where

import Data.Time (parseTimeM, defaultTimeLocale)
import Data.Time.LocalTime (LocalTime, localTimeOfDay, todHour, todMin)
import Data.ByteString.Lazy (ByteString)
import Network.HTTP.Simple (httpLBS, parseRequest, getResponseBody)
import Text.XML.Light

type Weather = (Double, Double, Int, Int)

fetchWeather :: IO ByteString
fetchWeather = do
  request <- parseRequest "http://meteo2.ftj.agh.edu.pl/meteo/meteo.xml"
  getResponseBody <$> httpLBS request

getWeather :: IO (Maybe Weather)
getWeather = parseWeather <$> fetchWeather

parseMeteoTime :: String -> Maybe LocalTime
parseMeteoTime time = parseTimeM True defaultTimeLocale "%F %T%Z" $ time ++ "00"

parseWeather :: ByteString -> Maybe Weather
parseWeather xml = do
  root <- parseXMLDoc xml >>= findChild (QName "dane_aktualne" Nothing Nothing)
  dateTime <- findAttr (QName "data" Nothing Nothing) root >>= parseMeteoTime
  temp <- read . head . words . strContent <$> findChild (QName "ta" Nothing Nothing) root
  humid <- read . head . words . strContent <$> findChild (QName "ua" Nothing Nothing) root
  let time = localTimeOfDay dateTime
  return (temp, humid, todHour time, todMin time)
